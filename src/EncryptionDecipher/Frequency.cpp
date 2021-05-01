// English frequency table
// 
// english 26x26 frequency count table as a single 676 element array read by
// row by row into the array. The upper left of matrix is the entry
// for aa and the upper right is az. In the array below we begin aa ab
// ac ad... az ba bb ... zz.   You can use the linear array to speed up
// the fitness calcuation if you want or you can convert to a 2D array 
// if you feel more comfortable with that.
// 
double english[26][26] =
{11, 122, 298, 210, 19, 54, 116, 23, 254, 6, 154, 632, 231, 1614, 11, 105, 1,
861, 451, 973, 123, 214, 55, 13, 225, 16, 108, 31, 1, 1, 597, 0, 0, 1, 94, 5,
0, 155, 4, 0, 137, 0, 0, 81, 28, 5, 184, 1, 1, 0, 118, 0, 348, 8, 32, 0, 411,
0, 2, 398, 133, 0, 136, 77, 1, 1, 379, 0, 1, 95, 23, 207, 61, 0, 0, 0, 32, 0,
166, 12, 6, 29, 405, 5, 23, 9, 287, 3, 1, 28, 8, 25, 274, 4, 1, 88, 105, 12,
41, 12, 15, 0, 44, 0, 659, 20, 223, 497, 319, 95, 54, 22, 167, 1, 25, 359,
218, 918, 109, 122, 16, 1478, 779, 334, 19, 246, 80, 125, 167, 6, 99, 1, 4,
1, 228, 81, 1, 5, 172, 0, 0, 34, 2, 1, 299, 3, 0, 223, 6, 69, 100, 0, 2, 0,
8, 0, 117, 0, 0, 0, 270, 0, 28, 227, 117, 0, 0, 49, 4, 28, 184, 0, 0, 124,
82, 14, 48, 1, 2, 0, 20, 0, 890, 2, 1, 2, 2061, 5, 0, 1, 600, 0, 0, 8, 8, 22,
465, 1, 0, 59, 14, 152, 89, 1, 7, 0, 43, 0, 110, 71, 372, 190, 288, 239, 218,
1, 5, 2, 90, 385, 233, 1784, 300, 44, 9, 222, 872, 847, 18, 182, 1, 13, 0,
40, 22, 0, 0, 0, 25, 0, 0, 0, 3, 0, 2, 0, 0, 0, 58, 0, 0, 2, 0, 1, 72, 0, 0,
0, 0, 0, 32, 3, 1, 0, 315, 1, 1, 2, 99, 0, 0, 8, 0, 79, 14, 0, 0, 6, 44, 0,
1, 0, 0, 1, 23, 0, 317, 19, 4, 254, 609, 55, 1, 0, 571, 0, 27, 556, 19, 6,
277, 11, 0, 7, 94, 48, 56, 29, 22, 0, 255, 0, 518, 69, 4, 1, 573, 9, 0, 0,
217, 0, 0, 8, 49, 9, 287, 137, 0, 3, 47, 2, 71, 0, 0, 0, 115, 0, 183, 9, 217,
919, 598, 31, 810, 10, 236, 20, 75, 72, 13, 67, 544, 5, 11, 11, 278, 528, 43,
28, 7, 1, 101, 2, 34, 96, 77, 160, 66, 676, 74, 40, 80, 2, 57, 200, 436,
1134, 223, 144, 1, 827, 209, 393, 1003, 152, 263, 16, 43, 10, 160, 2, 0, 1,
333, 0, 0, 56, 100, 0, 0, 166, 7, 0, 188, 72, 0, 202, 37, 50, 64, 0, 0, 0,
28, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 74, 0, 0,
0, 0, 0, 377, 62, 60, 173, 1196, 32, 57, 12, 401, 0, 72, 97, 78, 127, 524,
27, 0, 107, 295, 300, 119, 33, 5, 2, 224, 0, 204, 8, 106, 11, 568, 14, 4,
221, 312, 1, 34, 56, 47, 36, 298, 122, 5, 4, 242, 772, 166, 1, 28, 0, 23, 0,
351, 9, 43, 2, 679, 7, 2, 2624, 591, 1, 0, 79, 7, 9, 748, 5, 0, 255, 212,
146, 133, 5, 71, 0, 183, 8, 61, 46, 88, 32, 57, 17, 114, 2, 64, 1, 4, 228,
136, 312, 11, 94, 0, 414, 321, 349, 1, 0, 1, 4, 5, 3, 49, 0, 0, 0, 736, 0, 0,
0, 176, 0, 0, 0, 0, 0, 43, 0, 0, 1, 0, 0, 3, 0, 0, 0, 1, 0, 316, 0, 0, 3,
327, 2, 0, 434, 353, 0, 1, 13, 2, 49, 229, 1, 0, 29, 20, 6, 0, 0, 4, 0, 3, 0,
12, 0, 17, 0, 13, 1, 0, 1, 19, 0, 0, 0, 1, 0, 3, 48, 0, 0, 0, 23, 5, 0, 1, 1,
3, 0, 26, 18, 11, 4, 71, 3, 5, 2, 40, 0, 1, 8, 17, 7, 449, 8, 0, 7, 86, 58,
1, 0, 10, 1, 0, 1, 22, 0, 2, 0, 25, 0, 0, 0, 12, 0, 0, 0, 0, 0, 9, 0, 0, 0,
0, 1, 7, 0, 1, 0, 4, 3};