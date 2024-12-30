const float GLIDE_TIME_MS = 60;
const uint8_t HELD_NOTES_COUNT = 8;
const float MAX_CROSS_MODULATION_DEPTH = 10.0;
const float MAX_OSC_LEVEL = 0.2;
const float MAX_OSC_LFO_AMPLITUDE = 0.1;
const float MAX_PITCH_ENVELOPE_DEPTH = 0.3;

const float PROGMEM CONSTANT_POWER[128] = {0.00000, 0.08874, 0.12549, 0.15369, 0.17747, 0.19842, 0.21736, 0.23477, 0.25098, 0.26621, 0.28061, 0.29430, 0.30739, 0.31994, 0.33202, 0.34367, 0.35494, 0.36587, 0.37647, 0.38679, 0.39684, 0.40664, 0.41621, 0.42556, 0.43471, 0.44368, 0.45246, 0.46108, 0.46954, 0.47786, 0.48603, 0.49406, 0.50196, 0.50975, 0.51741, 0.52497, 0.53241, 0.53976, 0.54700, 0.55415, 0.56121, 0.56819, 0.57507, 0.58188, 0.58861, 0.59526, 0.60183, 0.60834, 0.61478, 0.62115, 0.62746, 0.63370, 0.63988, 0.64601, 0.65207, 0.65808, 0.66404, 0.66994, 0.67579, 0.68159, 0.68734, 0.69305, 0.69871, 0.70432, 0.70989, 0.71541, 0.72089, 0.72633, 0.73173, 0.73709, 0.74242, 0.74770, 0.75295, 0.75816, 0.76333, 0.76847, 0.77358, 0.77865, 0.78369, 0.78870, 0.79368, 0.79862, 0.80354, 0.80842, 0.81328, 0.81810, 0.82290, 0.82767, 0.83241, 0.83713, 0.84182, 0.84648, 0.85112, 0.85574, 0.86032, 0.86489, 0.86943, 0.87394, 0.87844, 0.88291, 0.88736, 0.89178, 0.89619, 0.90057, 0.90493, 0.90927, 0.91359, 0.91789, 0.92217, 0.92643, 0.93067, 0.93489, 0.93909, 0.94327, 0.94744, 0.95158, 0.95571, 0.95982, 0.96392, 0.96799, 0.97205, 0.97609, 0.98012, 0.98413, 0.98812, 0.99209, 0.99606, 1.00000};
const uint16_t PROGMEM ENV_TIMES_MS[128] = {1, 2, 4, 6, 9, 14, 20, 26, 33, 41, 49, 58, 67, 78, 89, 99, 111, 124, 136, 150, 164, 178, 192, 209, 224, 241, 258, 276, 295, 314, 333, 353, 374, 395, 418, 440, 464, 489, 513, 539, 565, 592, 621, 650, 680, 710, 742, 774, 808, 843, 878, 915, 952, 991, 1031, 1073, 1114, 1158, 1202, 1250, 1297, 1346, 1396, 1448, 1502, 1558, 1614, 1676, 1735, 1794, 1864, 1923, 1994, 2065, 2136, 2207, 2289, 2360, 2443, 2525, 2620, 2702, 2797, 2891, 2985, 3092, 3186, 3292, 3410, 3516, 3634, 3752, 3882, 4012, 4142, 4272, 4413, 4567, 4708, 4862, 5027, 5180, 5357, 5522, 5699, 5888, 6077, 6278, 6478, 6691, 6903, 7127, 7351, 7587, 7835, 8083, 8343, 8614, 8885, 9169, 9464, 9770, 10077, 10408, 10738, 11080, 11434, 11700};
const uint16_t PROGMEM FILTER_CUTOFF_FREQS_HZ[256] = {20, 21, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 43, 44, 46, 47, 49, 50, 52, 53, 55, 57, 59, 61, 63, 65, 68, 70, 73, 76, 78, 81, 84, 87, 91, 94, 98, 102, 106, 110, 114, 119, 123, 128, 133, 138, 144, 149, 155, 161, 167, 174, 181, 187, 195, 202, 210, 218, 226, 234, 243, 252, 261, 271, 281, 291, 301, 312, 323, 334, 346, 358, 370, 383, 395, 409, 422, 436, 451, 465, 480, 496, 512, 528, 544, 561, 578, 596, 614, 633, 652, 671, 691, 711, 732, 753, 774, 796, 818, 841, 865, 888, 913, 937, 962, 988, 1014, 1041, 1068, 1096, 1124, 1152, 1182, 1211, 1242, 1272, 1304, 1335, 1368, 1401, 1434, 1468, 1503, 1538, 1574, 1610, 1647, 1684, 1722, 1761, 1800, 1840, 1881, 1922, 1964, 2006, 2049, 2093, 2137, 2182, 2227, 2274, 2320, 2368, 2416, 2465, 2515, 2565, 2616, 2668, 2720, 2773, 2827, 2881, 2936, 2992, 3049, 3106, 3164, 3223, 3283, 3343, 3404, 3466, 3529, 3592, 3656, 3721, 3787, 3853, 3921, 3989, 4058, 4127, 4198, 4269, 4341, 4414, 4488, 4563, 4638, 4715, 4792, 4870, 4949, 5029, 5109, 5191, 5273, 5357, 5441, 5526, 5612, 5699, 5787, 5876, 5965, 6056, 6147, 6240, 6333, 6427, 6523, 6619, 6716, 6814, 6913, 7013, 7114, 7216, 7319, 7424, 7529, 7635, 7742, 7850, 7959, 8069, 8180, 8292, 8405, 8519, 8634, 8751, 8868, 8986, 9106, 9226, 9348, 9471, 9594, 9719, 9845, 9972, 10100, 10230, 10360, 10491, 10624, 10758, 10893, 11029, 11166, 11304, 11443, 11584, 11726, 11869, 12000};
const float PROGMEM LFO_FREQS_HZ[128] = {0.10000, 0.10140, 0.10561, 0.11263, 0.12245, 0.13508, 0.15051, 0.16875, 0.18980, 0.21365, 0.24031, 0.26977, 0.30204, 0.33712, 0.37500, 0.41569, 0.45918, 0.50548, 0.55459, 0.60651, 0.66122, 0.71875, 0.77908, 0.84222, 0.90816, 0.97691, 1.04847, 1.12283, 1.20000, 1.27997, 1.36276, 1.44834, 1.53673, 1.62793, 1.72194, 1.81875, 1.91837, 2.02079, 2.12602, 2.23406, 2.34490, 2.45855, 2.57500, 2.69426, 2.81633, 2.94120, 3.06888, 3.19936, 3.33265, 3.46875, 3.60765, 3.74936, 3.89388, 4.04120, 4.19133, 4.34426, 4.50000, 4.65855, 4.81990, 4.98406, 5.15102, 5.32079, 5.49337, 5.66875, 5.84694, 6.02793, 6.21173, 6.39834, 6.58776, 6.77997, 6.97500, 7.17283, 7.37347, 7.57691, 7.78316, 7.99222, 8.20408, 8.41875, 8.63622, 8.85651, 9.07959, 9.30548, 9.53418, 9.76569, 10.00000, 10.53542, 12.14170, 14.81882, 18.56679, 23.38561, 29.27528, 36.23580, 44.26717, 53.36939, 63.54246, 74.78637, 87.10114, 100.48675, 114.94321, 130.47052, 147.06869, 164.73770, 183.47756, 203.28826, 224.16982, 246.12223, 269.14548, 293.23959, 318.40454, 344.64035, 371.94700, 400.32450, 429.77285, 460.29205, 491.88210, 524.54300, 558.27474, 593.07734, 628.95078, 665.89508, 703.91022, 742.99621, 783.15306, 824.38075, 866.67929, 910.04867, 954.48891, 1000.00000};
const float PROGMEM NOTE_FREQ_DC[128] = {-0.57500, -0.56667, -0.55833, -0.55000, -0.54167, -0.53333, -0.52500, -0.51667, -0.50833, -0.50000, -0.49167, -0.48333, -0.47500, -0.46667, -0.45833, -0.45000, -0.44167, -0.43333, -0.42500, -0.41667, -0.40833, -0.40000, -0.39167, -0.38333, -0.37500, -0.36667, -0.35833, -0.35000, -0.34167, -0.33333, -0.32500, -0.31667, -0.30833, -0.30000, -0.29167, -0.28333, -0.27500, -0.26667, -0.25833, -0.25000, -0.24167, -0.23333, -0.22500, -0.21667, -0.20833, -0.20000, -0.19167, -0.18333, -0.17500, -0.16667, -0.15833, -0.15000, -0.14167, -0.13333, -0.12500, -0.11667, -0.10833, -0.10000, -0.09167, -0.08333, -0.07500, -0.06667, -0.05833, -0.05000, -0.04167, -0.03333, -0.02500, -0.01667, -0.00833, 0.00000, 0.00833, 0.01667, 0.02500, 0.03333, 0.04167, 0.05000, 0.05833, 0.06667, 0.07500, 0.08333, 0.09167, 0.10000, 0.10833, 0.11667, 0.12500, 0.13333, 0.14167, 0.15000, 0.15833, 0.16667, 0.17500, 0.18333, 0.19167, 0.20000, 0.20833, 0.21667, 0.22500, 0.23333, 0.24167, 0.25000, 0.25833, 0.26667, 0.27500, 0.28333, 0.29167, 0.30000, 0.30833, 0.31667, 0.32500, 0.33333, 0.34167, 0.35000, 0.35833, 0.36667, 0.37500, 0.38333, 0.39167, 0.40000, 0.40833, 0.41667, 0.42500, 0.43333, 0.44167, 0.45000, 0.45833, 0.46667, 0.47500, 0.48333};
const float PROGMEM POWER[128] = {0.0f, 0.00009f, 0.0003f, 0.0006f, 0.001f, 0.0016f, 0.0022f, 0.003f, 0.004f, 0.005f, 0.0062f, 0.0075f, 0.0089f, 0.0105f, 0.0122f, 0.014f, 0.016f, 0.018f, 0.02f, 0.022f, 0.025f, 0.027f, 0.03f, 0.033f, 0.036f, 0.039f, 0.042f, 0.045f, 0.049f, 0.052f, 0.056f, 0.06f, 0.063f, 0.068f, 0.072f, 0.076f, 0.08f, 0.085f, 0.09f, 0.094f, 0.099f, 0.104f, 0.109f, 0.115f, 0.12f, 0.126f, 0.131f, 0.137f, 0.143f, 0.149f, 0.155f, 0.161f, 0.168f, 0.174f, 0.181f, 0.188f, 0.194f, 0.201f, 0.209f, 0.216f, 0.223f, 0.231f, 0.238f, 0.246f, 0.254f, 0.262f, 0.27f, 0.278f, 0.287f, 0.295f, 0.304f, 0.313f, 0.321f, 0.33f, 0.34f, 0.349f, 0.358f, 0.368f, 0.377f, 0.387f, 0.397f, 0.407f, 0.417f, 0.427f, 0.437f, 0.448f, 0.459f, 0.469f, 0.48f, 0.491f, 0.502f, 0.513f, 0.525f, 0.536f, 0.548f, 0.56f, 0.571f, 0.583f, 0.595f, 0.608f, 0.62f, 0.632f, 0.645f, 0.658f, 0.671f, 0.684f, 0.697f, 0.71f, 0.723f, 0.737f, 0.75f, 0.764f, 0.778f, 0.792f, 0.806f, 0.82f, 0.834f, 0.849f, 0.863f, 0.878f, 0.893f, 0.908f, 0.923f, 0.938f, 0.953f, 0.969f, 0.984f, 1.0f};