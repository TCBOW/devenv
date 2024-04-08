/***************************************************************
 * @file    main.c
 * @brief   prototype simulator of data transfer controller.
 * @author  Toshiaki Sato
 * @date    2020/01/04 New
 * @par
 * Copyright (c) 2020 Toshiaki Sato All rights reversed.
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>

#include <time.h>
#define R5_READY 0x00000001
#define R5_COMPL 0x80000000
#define FBUF 64
#define FNUM 300
#define ORIG_TIME  1674388803
#define FBUF_ADDR  0x0200000000000000
#define FRAME_ADDR 0x0500000010000000
#define FRAME_SIZE 0x0000000001000000

typedef struct {
    uint32_t  mode;
    uint32_t  repeat;
    uint32_t  stopfnum;
} repctl_t;
static repctl_t repctl;

typedef struct {
    uint32_t  num;
    struct TC {
        uint8_t hour;
        uint8_t min;
        uint8_t sec;
        uint8_t frame;
    } tc;
} frame_t;

char *datadir = {""};

uint32_t R5res = 0;
static uint64_t frame_add = FRAME_ADDR;
static uint64_t fbuf_add = FBUF_ADDR;

int getargs(int argc, char **argv)
{

    int c, flag = 2;
    const char *optstring = "Vvhd:t:s:";  /* define optstring */
    int longindex = 0, ival = 0;
    //    long lval = 0;
    //    char* ptr;
    //    opterr = 0;  /* disable error log */


    /* if flag  = 0, when it is find name, getopt_long return val. */
    /* if flag != 0, when it is find name, getopt_long return 0. flag store val */
    const struct option longopts[] = {
        /*      {       *name,            has_arg,   *flag,   val }, */
        {   "verbose",        no_argument,       0,   'V' },
        {   "version",        no_argument,       0,   'v' },
        {      "help",        no_argument,       0,   'h' },
        {      "mode",  required_argument,   &flag,   'm' },
        {    "repeat",  required_argument,   &flag,   'r' },
        {  "stopfnum",  required_argument,   &flag,   's' },
        {           0,                  0,       0,    0  }, // termination
    };

    while ((c = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
        switch (c) {
        case 'V': // verbose
            /* TODO set verbose function */
            break;

        case 'v': // version
            /* TODO set timestamp mode */
            break;

        case 'h': // help
            /* TODO set usage */
            break;

        case 'd': // datadir
            /* TODO set */
            datadir = optarg;
            printf("datadir = %s\n", optarg);
            break;

        case 'm': // mode
            /* TODO set */
            ival = atoi(optarg);
            printf("mode = %d\n", ival);
            repctl.mode = ival;
            break;

        case 'r': // mode
            /* TODO set */
            ival = atoi(optarg);
            printf("repeat = %d\n", ival);
            repctl.repeat = ival;
            break;

        case 's': // stop
            ival = atoi(optarg);
            printf("repeat = %d\n", ival);
            repctl.stopfnum = ival;
            break;
#if 0

        case 's': // source
            /* TODO set */
            lval = strtol(optarg, &ptr, 10);
            printf("source = %ld\n", lval);
            break;
#endif

        default: // default
            break;
        }
    }

    return 0;
}

typedef enum dir {
    INC,
    DEC,
} DIR;

typedef enum mode {
    NORMAL,
    PISTON,
} MODE;

typedef enum repeat {
    OFF,
    ON,
} REPEAT;

static int vsynccnt;
static int fbufcnt;
static int fbufflg;
static int setcnt;
static int setflg;
static DIR dirflg;
static DIR endflg;
static MODE mode;
static REPEAT repeat;

/****************************************************************
 * @fn      ssddrv_init
 * @brief   initialize values.
 * @param   void
 * @return  void
 * @sa
 * @detail
*****************************************************************/
void ssddrv_init(void)
{

    vsynccnt = 0;
    fbufcnt = 0;
    fbufflg = 0;
    setcnt = FBUF;
    setflg = 0;
    dirflg = INC;

    endflg = 0;
    //    mode = NORMAL;
    mode = PISTON;
    repeat = OFF;
    //    repeat = ON;
}

void vsync_handler(frame_t f[])
{

    vsynccnt++;

    if (dirflg == INC) {
        if (setflg == 1) {
            setcnt = 1;
            setflg = 0;
        } else {
            setcnt++;
        }
    } else if (dirflg == DEC) {
        if (setflg == 1) {
            setcnt--;
        } else {
            setcnt = FNUM;
            setflg = 0;
        }
    }

    if (fbufflg == 0) {
        fbufcnt++;
    } else {
        fbufcnt = 1;
        fbufflg = 0;
    }

    if ((vsynccnt % FBUF) == 0) {
        fbufflg = 1;
    }

    if ((setcnt % FNUM) == 0) {
        if (mode == NORMAL) {
            if (repeat == ON) {
                setflg = 1;
            } else if (repeat == OFF) {
                endflg = 1;
            }
        } else if (mode == PISTON) {
            if (repeat == ON) {
                if (setcnt == FNUM) {
                    dirflg = DEC;
                } else if (setcnt == 0) {
                    dirflg = INC;
                }

                setflg = 1;
            } else if (repeat == OFF) {
                if (setcnt == FNUM) {
                    dirflg = DEC;
                    setflg = 1;
                } else if (setcnt == 0) {
                    endflg = 1;
                }
            }
        }
    }

    frame_add = FRAME_ADDR + (FRAME_SIZE * setcnt);
    fbuf_add = FBUF_ADDR + (FRAME_SIZE * fbufcnt);

    printf("vcnt: %06d, fcnt: %02d, scnt: %03d, fb_add: %016llx, fr_add: %016llx\n",
           vsynccnt, fbufcnt, setcnt, fbuf_add, frame_add);

}

int main(int argc, char *args[])
{

    int ret = -1;
    //    char date[64];
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t frame = 0;
    ssddrv_init();

    if ((ret = getargs(argc, args)) != 0) {
        return ret;
    }

    frame_t *fbuf[FNUM];

    time_t t  = time(NULL);
    //    strftime(date, sizeof(date), "%Y/%m/%d %a %H: %M: %S", localtime(&t));
    t = ORIG_TIME;
    hour = (t / 3600 + 9) % 24;
    min = t / 60 % 60;
    sec = t % 60;
    printf("localtime : %08ld \n", t);
    printf("%02u 時%02u 分%02u 秒 %02u f \n", hour, min, sec, frame);

    for (int i = 0, j = 0; i < FNUM; i++, j++) {
        fbuf[i] = malloc(sizeof(frame_t));
        fbuf[i]->num = i + 1;

        if (i != 0) {
            if ((i % 60) == 0) {
                j -= 60;
                sec++;

                if ((i / 60 % 60) == 0) {
                    sec -= 60;
                    min++;
                }

                if (((i / 3600 + 9) % 24) == 0) {
                    min -= 60;
                    hour++;
                }
            }
        }

        fbuf[i]->tc.hour = hour;
        fbuf[i]->tc.min = min;
        fbuf[i]->tc.sec = sec;
        fbuf[i]->tc.frame = j;
        printf("No.%04u %02u 時%02u 分%02u 秒 %02u f \n", fbuf[i]->num,
               fbuf[i]->tc.hour, fbuf[i]->tc.min, fbuf[i]->tc.sec, fbuf[i]->tc.frame);
    }

    R5res |= R5_COMPL;
    printf("R5res |= R5_COMPL = %d\n", R5res);

    for (; (R5res & R5_COMPL) == 0;) {}

    R5res = R5_READY;
    printf("R5res = R5_READY = %d\n", R5res);

    for (; (R5res & R5_READY) == 0;) {}

    while (endflg == 0) {
        vsync_handler(fbuf[0]);
    }

    for (int i = 0; i < FNUM; i++) {
        free(fbuf[i]);
    }


    return ret;
}
