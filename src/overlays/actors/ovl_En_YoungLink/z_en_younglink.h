#ifndef Z_EN_YOUNGLINK_H
#define Z_EN_YOUNGLINK_H

#include "ultra64.h"
#include "actor.h"
#include "assets/objects/object_link_child/object_link_child.h"

struct EnYoungLink;

typedef void (*EnYoungLinkActionFunc)(struct EnYoungLink*, struct PlayState*);

typedef struct EnYoungLink {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ Vec3s jointTable[17];  // Adjust to match skeleton limb count
    /* 0x01F6 */ Vec3s morphTable[17];
    /* 0x025C */ EnYoungLinkActionFunc actionFunc;
    /* 0x0260 */ s16 blinkTimer;
    /* 0x0262 */ s16 eyeIndex;
    /* 0x0264 */ u8 padding[0x04];
} EnYoungLink; // size = 0x268

#endif
