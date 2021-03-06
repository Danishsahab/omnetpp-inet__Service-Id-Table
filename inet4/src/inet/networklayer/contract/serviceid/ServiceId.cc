// src/inet/networklayer/contract/serviceid/ServiceId.cc

#include "inet/networklayer/contract/serviceid/ServiceId.h"

namespace inet {

static const int SERVICEID_STRING_SIZE = 20;

// predefined Sid
const ServiceId ServiceId::UNSPECIFIED__MTC_Sid;

bool ServiceId::parseServiceId(const char *text, unsigned char tobytes[]) {
    if (!text) return false;

    if (!strcmp(text, "<unspec>")) {
        tobytes[0] = tobytes[1] = 0;
        return true;
    }

    const char *s = text;
    int i = 0;
    while (true) {
        if (*s < '0' || *s > '9') return false; // missing number

        // read and store number
        int num = 0;
        while (*s >= '0' && *s <= '9') num = 10 * num + (*s++ - '0');
        if (num > 255) return false; // number too big
        tobytes[i++] = (unsigned char)num;

        if (!*s) break; // end of string
        if (*s != '.') return false; // invalid char after number
        if (i == 2) return false; // read 4th number and not yet EOS

        // skip '.'
        s++;
    }
    return i == 2;    // must have all 4 numbers
}

void ServiceId::set(int i0, int i1) {
    addr = (i0 << 8) | i1;
}

void ServiceId::set(const char *text) {
    unsigned char buf[2];
    if (!text) throw cRuntimeError("ServiceId string is nullptr");

    bool ok = parseServiceId(text, buf);
    if (!ok) throw cRuntimeError("Invalid ServiceId string `%s'", text);

    set(buf[0], buf[1]);
}

ServiceId::SidCategory ServiceId::getSidCategory() const {
    if (isUnspecified()) return UNSPECIFIED_MTC; // 0000 0000 0000 0000
    return UNSPECIFIED_MTC;
}

std::string ServiceId::str(bool printUnspec    /* = true */) const {
    if (printUnspec && isUnspecified()) return std::string("<unspec>");
    char buf[SERVICEID_STRING_SIZE];
    sprintf(buf, "%u.%u", (addr >> 8) & 255, addr & 255);
    return std::string(buf);
}

} // namespace inet

