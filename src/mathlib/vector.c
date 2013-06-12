#include "vector.h"

const sge_vec4f_aligned sge_vec4f_no_fraction = {8388608.0f,8388608.0f,8388608.0f,8388608.0f};
const sge_vec4f_aligned sge_vec4f_1000 = {1.0f, 0.0f, 0.0f, 0.0f};
const sge_vec4f_aligned sge_vec4f_0100 = {0.0f, 1.0f, 0.0f, 0.0f};
const sge_vec4f_aligned sge_vec4f_0010 = {0.0f, 0.0f, 1.0f, 0.0f};
const sge_vec4f_aligned sge_vec4f_0001 = {0.0f, 0.0f, 0.0f, 1.0f};

const sge_vec4f_aligned sge_vec4f_neg_1000 = {-1.0f, 0.0f, 0.0f, 0.0f};
const sge_vec4f_aligned sge_vec4f_neg_0100 = {0.0f, -1.0f, 0.0f, 0.0f};
const sge_vec4f_aligned sge_vec4f_neg_0010 = {0.0f, 0.0f, -1.0f, 0.0f};
const sge_vec4f_aligned sge_vec4f_neg_0001 = {0.0f, 0.0f, 0.0f, -1.0f};


const sge_vec4i_aligned sge_abs_mask = {0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF};
const sge_vec4i_aligned sge_onehalf_eps= { 0x3EFFFFFD, 0x3EFFFFFD, 0x3EFFFFFD, 0x3EFFFFFD};
const sge_vec4i_aligned sge_x_mask= { 0xFFFFFFFF, 0, 0, 0};
const sge_vec4i_aligned sge_y_mask= { 0, 0xFFFFFFFF, 0, 0};
const sge_vec4i_aligned sge_z_mask= { 0, 0, 0xFFFFFFFF, 0};
const sge_vec4i_aligned sge_w_mask= { 0, 0, 0, 0xFFFFFFFF};


