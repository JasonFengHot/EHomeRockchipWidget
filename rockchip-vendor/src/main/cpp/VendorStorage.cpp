//
// Created by wangchao on 2021/10/18.
//

#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>

#include "Log.h"
#include "VendorStorage.h"


#define VENDOR_SN_ID            1
#define VENDOR_REQ_TAG          0x56524551
#define VENDOR_READ_IO          _IOW('v', 0x01, unsigned int)
#define VENDOR_WRITE_IO         _IOW('v', 0x02, unsigned int)

#define SERIALNO_BUF_LEN 33
#define SN_SECTOR_OP_TAG            0x41444E53 // "SNDA"
#define RKNAND_GET_SN_SECTOR       _IOW('d', 3, unsigned int)

#define RKNAND_SYS_STORGAE_DATA_LEN 512

struct rk_vendor_req {
    uint32_t tag;
    uint16_t id;
    uint16_t len;
    uint8_t data[RKNAND_SYS_STORGAE_DATA_LEN];
};

void rknand_print_hex_data(uint8_t *s, uint32_t *buf, uint32_t len) {
    uint32_t i;
    LOGD("%s", s);
    for (i = 0; i < len; i += 4) {
        LOGD("%x %x %x %x", buf[i], buf[i + 1], buf[i + 2], buf[i + 3]);
    }
}

static char sn_buf_idb[SERIALNO_BUF_LEN] = {0};

std::string vendor_storage_read_sn() {
    int ret;
    uint16_t len;

    struct rk_vendor_req req{};

    memset(sn_buf_idb, 0, sizeof(sn_buf_idb));

    int sys_fd = open("/dev/vendor_storage", O_RDONLY, 0);
    if (sys_fd < 0) {
        LOGE("/dev/vendor_storage open fail !");
    }

    req.tag = VENDOR_REQ_TAG;
    req.id = VENDOR_SN_ID;
    req.len = RKNAND_SYS_STORGAE_DATA_LEN; /* max read length to read*/
    ret = ioctl(sys_fd, VENDOR_READ_IO, &req);
    close(sys_fd);

    rknand_print_hex_data((uint8_t *) "vendor_storage read:", (uint32_t *) req.data, req.len / 4 + 3);

    LOGD("data length： %d", req.len / 4 + 3);
    /* return req->len is the real data length stored in the NV-storage */
    if (ret) {
        LOGE("/dev/vendor_storage read error\n");
    }

    //get the sn length
    len = req.len;

    LOGD("serialnumber length： %d", len);

    if (len <= 0) {
        LOGE("serialnumber length <= 0");
        return "NULL";
    }

    memcpy(sn_buf_idb, req.data, len);

    LOGD("vendor_storage read sn_buf_idb:%s\n", sn_buf_idb);

    std::string serialNumber(sn_buf_idb);

    return serialNumber;
}

int vendor_storage_write_sn(const char *sn) {
    LOGD("write serialnumber: %s to IDB.\n", sn);
    int ret;
    struct rk_vendor_req req{};

    int sys_fd = open("/dev/vendor_storage", O_RDONLY, 0);
    if (sys_fd < 0) {
        LOGE("vendor_storage open fail !");
        return -1;
    }
    memset(&req, 0, sizeof(req));
    req.tag = VENDOR_REQ_TAG;
    req.id = VENDOR_SN_ID;
    req.len = strlen(sn);
    memcpy(req.data, sn, strlen(sn));
    rknand_print_hex_data((uint8_t *) "vendor_storage write:", (uint32_t *) req.data, req.len / 4 + 3);
    ret = ioctl(sys_fd, VENDOR_WRITE_IO, &req);
    close(sys_fd);
    if (ret) {
        LOGE("vendor_storage error in writing SN to IDB.\n");
        return -1;
    }
    return 0;
}


std::string VendorStorage::getSerialNumber() {
    return vendor_storage_read_sn();
}

void VendorStorage::putSerialNumber(std::string number) {
    vendor_storage_write_sn(number.c_str());
}
