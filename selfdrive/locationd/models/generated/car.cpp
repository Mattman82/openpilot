#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2053284186493430191) {
   out_2053284186493430191[0] = delta_x[0] + nom_x[0];
   out_2053284186493430191[1] = delta_x[1] + nom_x[1];
   out_2053284186493430191[2] = delta_x[2] + nom_x[2];
   out_2053284186493430191[3] = delta_x[3] + nom_x[3];
   out_2053284186493430191[4] = delta_x[4] + nom_x[4];
   out_2053284186493430191[5] = delta_x[5] + nom_x[5];
   out_2053284186493430191[6] = delta_x[6] + nom_x[6];
   out_2053284186493430191[7] = delta_x[7] + nom_x[7];
   out_2053284186493430191[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6698103364938640629) {
   out_6698103364938640629[0] = -nom_x[0] + true_x[0];
   out_6698103364938640629[1] = -nom_x[1] + true_x[1];
   out_6698103364938640629[2] = -nom_x[2] + true_x[2];
   out_6698103364938640629[3] = -nom_x[3] + true_x[3];
   out_6698103364938640629[4] = -nom_x[4] + true_x[4];
   out_6698103364938640629[5] = -nom_x[5] + true_x[5];
   out_6698103364938640629[6] = -nom_x[6] + true_x[6];
   out_6698103364938640629[7] = -nom_x[7] + true_x[7];
   out_6698103364938640629[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2176330126114191271) {
   out_2176330126114191271[0] = 1.0;
   out_2176330126114191271[1] = 0;
   out_2176330126114191271[2] = 0;
   out_2176330126114191271[3] = 0;
   out_2176330126114191271[4] = 0;
   out_2176330126114191271[5] = 0;
   out_2176330126114191271[6] = 0;
   out_2176330126114191271[7] = 0;
   out_2176330126114191271[8] = 0;
   out_2176330126114191271[9] = 0;
   out_2176330126114191271[10] = 1.0;
   out_2176330126114191271[11] = 0;
   out_2176330126114191271[12] = 0;
   out_2176330126114191271[13] = 0;
   out_2176330126114191271[14] = 0;
   out_2176330126114191271[15] = 0;
   out_2176330126114191271[16] = 0;
   out_2176330126114191271[17] = 0;
   out_2176330126114191271[18] = 0;
   out_2176330126114191271[19] = 0;
   out_2176330126114191271[20] = 1.0;
   out_2176330126114191271[21] = 0;
   out_2176330126114191271[22] = 0;
   out_2176330126114191271[23] = 0;
   out_2176330126114191271[24] = 0;
   out_2176330126114191271[25] = 0;
   out_2176330126114191271[26] = 0;
   out_2176330126114191271[27] = 0;
   out_2176330126114191271[28] = 0;
   out_2176330126114191271[29] = 0;
   out_2176330126114191271[30] = 1.0;
   out_2176330126114191271[31] = 0;
   out_2176330126114191271[32] = 0;
   out_2176330126114191271[33] = 0;
   out_2176330126114191271[34] = 0;
   out_2176330126114191271[35] = 0;
   out_2176330126114191271[36] = 0;
   out_2176330126114191271[37] = 0;
   out_2176330126114191271[38] = 0;
   out_2176330126114191271[39] = 0;
   out_2176330126114191271[40] = 1.0;
   out_2176330126114191271[41] = 0;
   out_2176330126114191271[42] = 0;
   out_2176330126114191271[43] = 0;
   out_2176330126114191271[44] = 0;
   out_2176330126114191271[45] = 0;
   out_2176330126114191271[46] = 0;
   out_2176330126114191271[47] = 0;
   out_2176330126114191271[48] = 0;
   out_2176330126114191271[49] = 0;
   out_2176330126114191271[50] = 1.0;
   out_2176330126114191271[51] = 0;
   out_2176330126114191271[52] = 0;
   out_2176330126114191271[53] = 0;
   out_2176330126114191271[54] = 0;
   out_2176330126114191271[55] = 0;
   out_2176330126114191271[56] = 0;
   out_2176330126114191271[57] = 0;
   out_2176330126114191271[58] = 0;
   out_2176330126114191271[59] = 0;
   out_2176330126114191271[60] = 1.0;
   out_2176330126114191271[61] = 0;
   out_2176330126114191271[62] = 0;
   out_2176330126114191271[63] = 0;
   out_2176330126114191271[64] = 0;
   out_2176330126114191271[65] = 0;
   out_2176330126114191271[66] = 0;
   out_2176330126114191271[67] = 0;
   out_2176330126114191271[68] = 0;
   out_2176330126114191271[69] = 0;
   out_2176330126114191271[70] = 1.0;
   out_2176330126114191271[71] = 0;
   out_2176330126114191271[72] = 0;
   out_2176330126114191271[73] = 0;
   out_2176330126114191271[74] = 0;
   out_2176330126114191271[75] = 0;
   out_2176330126114191271[76] = 0;
   out_2176330126114191271[77] = 0;
   out_2176330126114191271[78] = 0;
   out_2176330126114191271[79] = 0;
   out_2176330126114191271[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7949722620898716144) {
   out_7949722620898716144[0] = state[0];
   out_7949722620898716144[1] = state[1];
   out_7949722620898716144[2] = state[2];
   out_7949722620898716144[3] = state[3];
   out_7949722620898716144[4] = state[4];
   out_7949722620898716144[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7949722620898716144[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7949722620898716144[7] = state[7];
   out_7949722620898716144[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6365474199122608814) {
   out_6365474199122608814[0] = 1;
   out_6365474199122608814[1] = 0;
   out_6365474199122608814[2] = 0;
   out_6365474199122608814[3] = 0;
   out_6365474199122608814[4] = 0;
   out_6365474199122608814[5] = 0;
   out_6365474199122608814[6] = 0;
   out_6365474199122608814[7] = 0;
   out_6365474199122608814[8] = 0;
   out_6365474199122608814[9] = 0;
   out_6365474199122608814[10] = 1;
   out_6365474199122608814[11] = 0;
   out_6365474199122608814[12] = 0;
   out_6365474199122608814[13] = 0;
   out_6365474199122608814[14] = 0;
   out_6365474199122608814[15] = 0;
   out_6365474199122608814[16] = 0;
   out_6365474199122608814[17] = 0;
   out_6365474199122608814[18] = 0;
   out_6365474199122608814[19] = 0;
   out_6365474199122608814[20] = 1;
   out_6365474199122608814[21] = 0;
   out_6365474199122608814[22] = 0;
   out_6365474199122608814[23] = 0;
   out_6365474199122608814[24] = 0;
   out_6365474199122608814[25] = 0;
   out_6365474199122608814[26] = 0;
   out_6365474199122608814[27] = 0;
   out_6365474199122608814[28] = 0;
   out_6365474199122608814[29] = 0;
   out_6365474199122608814[30] = 1;
   out_6365474199122608814[31] = 0;
   out_6365474199122608814[32] = 0;
   out_6365474199122608814[33] = 0;
   out_6365474199122608814[34] = 0;
   out_6365474199122608814[35] = 0;
   out_6365474199122608814[36] = 0;
   out_6365474199122608814[37] = 0;
   out_6365474199122608814[38] = 0;
   out_6365474199122608814[39] = 0;
   out_6365474199122608814[40] = 1;
   out_6365474199122608814[41] = 0;
   out_6365474199122608814[42] = 0;
   out_6365474199122608814[43] = 0;
   out_6365474199122608814[44] = 0;
   out_6365474199122608814[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6365474199122608814[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6365474199122608814[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6365474199122608814[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6365474199122608814[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6365474199122608814[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6365474199122608814[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6365474199122608814[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6365474199122608814[53] = -9.8000000000000007*dt;
   out_6365474199122608814[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6365474199122608814[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6365474199122608814[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6365474199122608814[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6365474199122608814[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6365474199122608814[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6365474199122608814[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6365474199122608814[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6365474199122608814[62] = 0;
   out_6365474199122608814[63] = 0;
   out_6365474199122608814[64] = 0;
   out_6365474199122608814[65] = 0;
   out_6365474199122608814[66] = 0;
   out_6365474199122608814[67] = 0;
   out_6365474199122608814[68] = 0;
   out_6365474199122608814[69] = 0;
   out_6365474199122608814[70] = 1;
   out_6365474199122608814[71] = 0;
   out_6365474199122608814[72] = 0;
   out_6365474199122608814[73] = 0;
   out_6365474199122608814[74] = 0;
   out_6365474199122608814[75] = 0;
   out_6365474199122608814[76] = 0;
   out_6365474199122608814[77] = 0;
   out_6365474199122608814[78] = 0;
   out_6365474199122608814[79] = 0;
   out_6365474199122608814[80] = 1;
}
void h_25(double *state, double *unused, double *out_4605634950602431443) {
   out_4605634950602431443[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6930059447020802318) {
   out_6930059447020802318[0] = 0;
   out_6930059447020802318[1] = 0;
   out_6930059447020802318[2] = 0;
   out_6930059447020802318[3] = 0;
   out_6930059447020802318[4] = 0;
   out_6930059447020802318[5] = 0;
   out_6930059447020802318[6] = 1;
   out_6930059447020802318[7] = 0;
   out_6930059447020802318[8] = 0;
}
void h_24(double *state, double *unused, double *out_451272640656486529) {
   out_451272640656486529[0] = state[4];
   out_451272640656486529[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1118673815998025353) {
   out_1118673815998025353[0] = 0;
   out_1118673815998025353[1] = 0;
   out_1118673815998025353[2] = 0;
   out_1118673815998025353[3] = 0;
   out_1118673815998025353[4] = 1;
   out_1118673815998025353[5] = 0;
   out_1118673815998025353[6] = 0;
   out_1118673815998025353[7] = 0;
   out_1118673815998025353[8] = 0;
   out_1118673815998025353[9] = 0;
   out_1118673815998025353[10] = 0;
   out_1118673815998025353[11] = 0;
   out_1118673815998025353[12] = 0;
   out_1118673815998025353[13] = 0;
   out_1118673815998025353[14] = 1;
   out_1118673815998025353[15] = 0;
   out_1118673815998025353[16] = 0;
   out_1118673815998025353[17] = 0;
}
void h_30(double *state, double *unused, double *out_968185422348409093) {
   out_968185422348409093[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6988988296561141100) {
   out_6988988296561141100[0] = 0;
   out_6988988296561141100[1] = 0;
   out_6988988296561141100[2] = 0;
   out_6988988296561141100[3] = 0;
   out_6988988296561141100[4] = 1;
   out_6988988296561141100[5] = 0;
   out_6988988296561141100[6] = 0;
   out_6988988296561141100[7] = 0;
   out_6988988296561141100[8] = 0;
}
void h_26(double *state, double *unused, double *out_1636219898460288558) {
   out_1636219898460288558[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7775181307814693074) {
   out_7775181307814693074[0] = 0;
   out_7775181307814693074[1] = 0;
   out_7775181307814693074[2] = 0;
   out_7775181307814693074[3] = 0;
   out_7775181307814693074[4] = 0;
   out_7775181307814693074[5] = 0;
   out_7775181307814693074[6] = 0;
   out_7775181307814693074[7] = 1;
   out_7775181307814693074[8] = 0;
}
void h_27(double *state, double *unused, double *out_3982527731202409965) {
   out_3982527731202409965[0] = state[3];
}
void H_27(double *state, double *unused, double *out_9212582367745084317) {
   out_9212582367745084317[0] = 0;
   out_9212582367745084317[1] = 0;
   out_9212582367745084317[2] = 0;
   out_9212582367745084317[3] = 1;
   out_9212582367745084317[4] = 0;
   out_9212582367745084317[5] = 0;
   out_9212582367745084317[6] = 0;
   out_9212582367745084317[7] = 0;
   out_9212582367745084317[8] = 0;
}
void h_29(double *state, double *unused, double *out_4033487845312436552) {
   out_4033487845312436552[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7499219640875533284) {
   out_7499219640875533284[0] = 0;
   out_7499219640875533284[1] = 1;
   out_7499219640875533284[2] = 0;
   out_7499219640875533284[3] = 0;
   out_7499219640875533284[4] = 0;
   out_7499219640875533284[5] = 0;
   out_7499219640875533284[6] = 0;
   out_7499219640875533284[7] = 0;
   out_7499219640875533284[8] = 0;
}
void h_28(double *state, double *unused, double *out_5462455835776756925) {
   out_5462455835776756925[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8983894161268692081) {
   out_8983894161268692081[0] = 1;
   out_8983894161268692081[1] = 0;
   out_8983894161268692081[2] = 0;
   out_8983894161268692081[3] = 0;
   out_8983894161268692081[4] = 0;
   out_8983894161268692081[5] = 0;
   out_8983894161268692081[6] = 0;
   out_8983894161268692081[7] = 0;
   out_8983894161268692081[8] = 0;
}
void h_31(double *state, double *unused, double *out_4880829012886937332) {
   out_4880829012886937332[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6899413485143841890) {
   out_6899413485143841890[0] = 0;
   out_6899413485143841890[1] = 0;
   out_6899413485143841890[2] = 0;
   out_6899413485143841890[3] = 0;
   out_6899413485143841890[4] = 0;
   out_6899413485143841890[5] = 0;
   out_6899413485143841890[6] = 0;
   out_6899413485143841890[7] = 0;
   out_6899413485143841890[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_2053284186493430191) {
  err_fun(nom_x, delta_x, out_2053284186493430191);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6698103364938640629) {
  inv_err_fun(nom_x, true_x, out_6698103364938640629);
}
void car_H_mod_fun(double *state, double *out_2176330126114191271) {
  H_mod_fun(state, out_2176330126114191271);
}
void car_f_fun(double *state, double dt, double *out_7949722620898716144) {
  f_fun(state,  dt, out_7949722620898716144);
}
void car_F_fun(double *state, double dt, double *out_6365474199122608814) {
  F_fun(state,  dt, out_6365474199122608814);
}
void car_h_25(double *state, double *unused, double *out_4605634950602431443) {
  h_25(state, unused, out_4605634950602431443);
}
void car_H_25(double *state, double *unused, double *out_6930059447020802318) {
  H_25(state, unused, out_6930059447020802318);
}
void car_h_24(double *state, double *unused, double *out_451272640656486529) {
  h_24(state, unused, out_451272640656486529);
}
void car_H_24(double *state, double *unused, double *out_1118673815998025353) {
  H_24(state, unused, out_1118673815998025353);
}
void car_h_30(double *state, double *unused, double *out_968185422348409093) {
  h_30(state, unused, out_968185422348409093);
}
void car_H_30(double *state, double *unused, double *out_6988988296561141100) {
  H_30(state, unused, out_6988988296561141100);
}
void car_h_26(double *state, double *unused, double *out_1636219898460288558) {
  h_26(state, unused, out_1636219898460288558);
}
void car_H_26(double *state, double *unused, double *out_7775181307814693074) {
  H_26(state, unused, out_7775181307814693074);
}
void car_h_27(double *state, double *unused, double *out_3982527731202409965) {
  h_27(state, unused, out_3982527731202409965);
}
void car_H_27(double *state, double *unused, double *out_9212582367745084317) {
  H_27(state, unused, out_9212582367745084317);
}
void car_h_29(double *state, double *unused, double *out_4033487845312436552) {
  h_29(state, unused, out_4033487845312436552);
}
void car_H_29(double *state, double *unused, double *out_7499219640875533284) {
  H_29(state, unused, out_7499219640875533284);
}
void car_h_28(double *state, double *unused, double *out_5462455835776756925) {
  h_28(state, unused, out_5462455835776756925);
}
void car_H_28(double *state, double *unused, double *out_8983894161268692081) {
  H_28(state, unused, out_8983894161268692081);
}
void car_h_31(double *state, double *unused, double *out_4880829012886937332) {
  h_31(state, unused, out_4880829012886937332);
}
void car_H_31(double *state, double *unused, double *out_6899413485143841890) {
  H_31(state, unused, out_6899413485143841890);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
