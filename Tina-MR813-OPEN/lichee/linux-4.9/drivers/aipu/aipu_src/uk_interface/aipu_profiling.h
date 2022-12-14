/**********************************************************************************
 * This file is CONFIDENTIAL and any use by you is subject to the terms of the
 * agreement between you and Arm China or the terms of the agreement between you
 * and the party authorised by Arm China to disclose this file to you.
 * The confidential and proprietary information contained in this file
 * may only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from Arm China.
 *
 *        (C) Copyright 2020 Arm Technology (China) Co. Ltd.
 *                    All rights reserved.
 *
 * This entire notice must be reproduced on all copies of this file and copies of
 * this file may only be made by a person if such person is permitted to do so
 * under the terms of a subsisting license agreement from Arm China.
 *
 *********************************************************************************/

/**
 * @file aipu_profiling.h
 * UMD & KMD interface header of AIPU job profiling info.
 */

#ifndef _AIPU_PROFILING_H_
#define _AIPU_PROFILING_H_

#ifdef __KERNEL__
#include <linux/time.h>
#else
#include <sys/time.h>
#endif
#include <linux/types.h>

struct profiling_data {
        struct timeval sched_tv;
        struct timeval done_tv;
        __u32  rdata_tot_msb;
        __u32  rdata_tot_lsb;
        __u32  wdata_tot_msb;
        __u32  wdata_tot_lsb;
        __u32  tot_cycle_msb;
        __u32  tot_cycle_lsb;
};

#endif /* _AIPU_PROFILING_H_ */