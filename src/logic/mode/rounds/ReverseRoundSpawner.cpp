#include "ReverseRoundSpawner.h"
#include <iostream>

ReverseRoundSpawner::ReverseRoundSpawner() {
    init();
}

void ReverseRoundSpawner::init() {
    // Initialize the round templates for different rounds
    
    roundTemplates[1] = Round(121, {
        {BloonType::Red, {0, 0, 0}, 20, 0.00f, 17.51f}
    });
    roundTemplates[2] = Round(137, {
        {BloonType::Red, {0, 0, 0}, 35, 0.00f, 19.00f}
    });
    roundTemplates[3] = Round(138, {
        {BloonType::Red, {0, 0, 0}, 15, 0.00f, 7.00f},
        {BloonType::Blue, {0, 0, 0}, 5, 8.76f, 11.01f},
        {BloonType::Red, {0, 0, 0}, 10, 11.61f, 16.71f}
    });
    roundTemplates[4] = Round(175, {
        {BloonType::Red, {0, 0, 0}, 10, 0.00f, 2.80f},
        {BloonType::Blue, {0, 0, 0}, 18, 6.91f, 9.41f},
        {BloonType::Red, {0, 0, 0}, 25, 5.31f, 17.31f}
    });
    roundTemplates[5] = Round(164, {
        {BloonType::Blue, {0, 0, 0}, 15, 0.00f, 7.90f},
        {BloonType::Red, {0, 0, 0}, 5, 8.52f, 10.80f},
        {BloonType::Blue, {0, 0, 0}, 12, 11.36f, 16.50f}
    });
    roundTemplates[6] = Round(163, {
        {BloonType::Blue, {0, 0, 0}, 15, 0.00f, 7.90f},
        {BloonType::Red, {0, 0, 0}, 15, 8.37f, 13.37f},
        {BloonType::Green, {0, 0, 0}, 4, 16.99f, 18.70f}
    });
    roundTemplates[7] = Round(182, {
        {BloonType::Blue, {0, 0, 0}, 10, 0.00f, 3.99f},
        {BloonType::Red, {0, 0, 0}, 20, 4.15f, 14.99f},
        {BloonType::Green, {0, 0, 0}, 5, 16.15f, 21.10f},
        {BloonType::Blue, {0, 0, 0}, 10, 21.66f, 26.80f}
    });
    roundTemplates[8] = Round(200, {
        {BloonType::Green, {0, 0, 0}, 12, 0.00f, 10.60f},
        {BloonType::Red, {0, 0, 0}, 10, 12.87f, 14.84f},
        {BloonType::Green, {0, 0, 0}, 2, 16.88f, 17.45f},
        {BloonType::Blue, {0, 0, 0}, 20, 18.03f, 28.87f}
    });
    roundTemplates[9] = Round(199, {
        {BloonType::Green, {0, 0, 0}, 30, 0.00f, 18.95f}
    });
    roundTemplates[10] = Round(314, {
        {BloonType::Blue, {0, 0, 0}, 22, 0.00f, 3.99f},
        {BloonType::Blue, {0, 0, 0}, 20, 3.99f, 12.99f},
        {BloonType::Blue, {0, 0, 0}, 60, 12.99f, 47.99f}
    });
    roundTemplates[11] = Round(189, {
        {BloonType::Red, {0, 0, 0}, 10, 0.00f, 4.57f},
        {BloonType::Blue, {0, 0, 0}, 10, 4.49f, 8.29f},
        {BloonType::Green, {0, 0, 0}, 12, 8.41f, 14.69f},
        {BloonType::Yellow, {0, 0, 0}, 3, 18.16f, 19.16f}
    });
    roundTemplates[12] = Round(192, {
        {BloonType::Yellow, {0, 0, 0}, 5, 0.00f, 3.12f},
        {BloonType::Blue, {0, 0, 0}, 15, 5.62f, 11.69f},
        {BloonType::Green, {0, 0, 0}, 10, 12.26f, 17.39f}
    });
    roundTemplates[13] = Round(282, {
        {BloonType::Green, {0, 0, 0}, 23, 0.00f, 30.00f},
        {BloonType::Blue, {0, 0, 0}, 50, 2.21f, 32.21f}
    });
    roundTemplates[14] = Round(259, {
        {BloonType::Yellow, {0, 0, 0}, 5, 1.37f, 2.92f},
        {BloonType::Green, {0, 0, 0}, 5, 5.41f, 6.79f},
        {BloonType::Blue, {0, 0, 0}, 10, 9.29f, 10.67f},
        {BloonType::Red, {0, 0, 0}, 31, 0.00f, 17.13f},
        {BloonType::Yellow, {0, 0, 0}, 4, 17.12f, 18.07f},
        {BloonType::Green, {0, 0, 0}, 5, 19.80f, 20.92f},
        {BloonType::Blue, {0, 0, 0}, 5, 22.66f, 23.78f},
        {BloonType::Red, {0, 0, 0}, 18, 16.92f, 26.63f}
    });
    roundTemplates[15] = Round(266, {
        {BloonType::Pink, {0, 0, 0}, 5, 4.45f, 7.45f},
        {BloonType::Yellow, {0, 0, 0}, 10, 4.13f, 16.13f},
        {BloonType::Green, {0, 0, 0}, 12, 4.32f, 19.32f},
        {BloonType::Blue, {0, 0, 0}, 15, 2.22f, 22.22f},
        {BloonType::Red, {0, 0, 0}, 20, 0.00f, 25.00f}
    });
    roundTemplates[16] = Round(268, {
        {BloonType::Yellow, {0, 0, 0}, 8, 0.00f, 1.43f},
        {BloonType::Green, {0, 0, 0}, 20, 4.97f, 15.82f},
        {BloonType::Green, {0, 0, 0}, 20, 5.17f, 16.02f}
    });
    roundTemplates[17] = Round(165, {
        {BloonType::Yellow, {0, 0, 1}, 12, 0.00f, 5.00f}
    });
    roundTemplates[18] = Round(358, {
        {BloonType::Green, {0, 0, 0}, 20, 0.00f, 1.82f},
        {BloonType::Green, {0, 0, 0}, 60, 1.82f, 26.82f}
    });
    roundTemplates[19] = Round(260, {
        {BloonType::Yellow, {0, 0, 0}, 4, 0.00f, 2.28f},
        {BloonType::Pink, {0, 0, 0}, 15, 2.19f, 9.80f},
        {BloonType::Yellow, {0, 0, 0}, 5, 10.57f, 12.91f},
        {BloonType::Green, {0, 0, 0}, 10, 12.88f, 15.76f}
    });
    roundTemplates[20] = Round(186, {
        {BloonType::Black, {0, 0, 0}, 6, 0.00f, 5.25f}
    });
    roundTemplates[21] = Round(351, {
        {BloonType::Pink, {0, 0, 0}, 4, 0.09f, 1.53f},
        {BloonType::Pink, {0, 0, 0}, 10, 2.23f, 7.37f},
        {BloonType::Yellow, {0, 0, 0}, 40, 8.12f, 18.12f}
    });
    roundTemplates[22] = Round(298, {
        {BloonType::White, {0, 0, 0}, 16, 0.00f, 8.00f}
    });
    roundTemplates[23] = Round(277, {
        {BloonType::White, {0, 0, 0}, 7, 0.00f, 2.00f},
        {BloonType::Black, {0, 0, 0}, 7, 4.32f, 6.82f}
    });
    roundTemplates[24] = Round(167, {
        {BloonType::Blue, {0, 0, 0}, 20, 0.00f, 6.00f},
        {BloonType::Green, {0, 0, 0}, 1, 8.50f, 8.50f}
    });
    roundTemplates[25] = Round(335, {
        {BloonType::Purple, {0, 0, 0}, 10, 0.00f, 4.00f},
        {BloonType::Yellow, {0, 0, 0}, 25, 7.14f, 21.14f}
    });
    roundTemplates[26] = Round(333, {
        {BloonType::Zebra, {0, 0, 0}, 4, 0.00f, 3.43f},
        {BloonType::Pink, {0, 0, 0}, 23, 5.81f, 14.51f}
    });
    roundTemplates[27] = Round(662, {
        {BloonType::Yellow, {0, 0, 0}, 45, 0.02f, 7.75f},
        {BloonType::Green, {0, 0, 0}, 45, 7.88f, 15.22f},
        {BloonType::Blue, {0, 0, 0}, 60, 14.74f, 22.73f},
        {BloonType::Red, {0, 0, 0}, 100, 22.25f, 34.26f}
    });
    roundTemplates[28] = Round(266, {
        {BloonType::Lead, {0, 0, 0}, 6, 0.00f, 5.00f}
    });
    roundTemplates[29] = Round(389, {
        {BloonType::Yellow, {0, 0, 1}, 15, 0.00f, 2.50f},
        {BloonType::Yellow, {0, 0, 0}, 50, 4.25f, 15.25f}
    });
    roundTemplates[30] = Round(337, {
        {BloonType::Lead, {0, 0, 0}, 9, 0.00f, 13.07f}
    });
    roundTemplates[31] = Round(537, {
        {BloonType::Zebra, {0, 0, 1}, 2, 0.00f, 1.71f},
        {BloonType::Zebra, {0, 0, 0}, 8, 4.67f, 9.75f},
        {BloonType::White, {0, 0, 0}, 8, 10.48f, 15.56f},
        {BloonType::Black, {0, 0, 0}, 8, 10.83f, 15.91f}
    });
    roundTemplates[32] = Round(627, {
        {BloonType::Purple, {0, 0, 0}, 10, 0.00f, 6.00f},
        {BloonType::White, {0, 0, 0}, 20, 6.62f, 17.62f},
        {BloonType::Black, {0, 0, 0}, 15, 18.96f, 27.96f}
    });
    roundTemplates[33] = Round(205, {
        {BloonType::Yellow, {0, 1, 0}, 13, 0.00f, 20.00f},
        {BloonType::Red, {0, 0, 0}, 20, 20.34f, 25.34f}
    });
    roundTemplates[34] = Round(912, {
        {BloonType::Zebra, {0, 0, 0}, 6, 9.30f, 27.38f},
        {BloonType::Yellow, {0, 0, 0}, 160, 0.00f, 36.00f}
    });
    roundTemplates[35] = Round(1150, {
        {BloonType::Black, {0, 0, 0}, 30, 0.00f, 7.00f},
        {BloonType::Pink, {0, 0, 0}, 35, 7.55f, 14.54f},
        {BloonType::Rainbow, {0, 0, 0}, 5, 17.12f, 19.40f},
        {BloonType::White, {0, 0, 0}, 25, 23.72f, 33.76f}
    });
    roundTemplates[36] = Round(896, {
        {BloonType::Pink, {0, 0, 0}, 60, 0.00f, 4.00f},
        {BloonType::Green, {0, 0, 1}, 10, 6.97f, 8.32f},
        {BloonType::Pink, {0, 0, 0}, 40, 11.15f, 12.50f},
        {BloonType::Green, {0, 0, 0}, 10, 15.63f, 16.98f},
        {BloonType::Pink, {0, 0, 0}, 40, 19.48f, 20.99f}
    });
    roundTemplates[37] = Round(1339, {
        {BloonType::White, {0, 1, 0}, 7, 0.00f, 1.59f},
        {BloonType::Zebra, {0, 0, 0}, 10, 6.96f, 12.10f},
        {BloonType::Lead, {0, 0, 0}, 15, 12.67f, 20.67f},
        {BloonType::White, {0, 0, 0}, 25, 21.24f, 32.09f},
        {BloonType::Black, {0, 0, 0}, 25, 32.66f, 43.51f}
    });
    roundTemplates[38] = Round(1277, {
        {BloonType::Ceramic, {0, 0, 0}, 2, 0.00f, 2.00f},
        {BloonType::Zebra, {0, 0, 0}, 10, 10.69f, 16.97f},
        {BloonType::Lead, {0, 0, 0}, 14, 15.66f, 24.23f},
        {BloonType::Pink, {0, 0, 0}, 42, 3.65f, 27.06f},
        {BloonType::White, {0, 0, 0}, 17, 25.46f, 29.06f}
    });
    roundTemplates[39] = Round(1759, {
        {BloonType::Rainbow, {0, 0, 1}, 2, 0.00f, 2.00f},
        {BloonType::Rainbow, {0, 0, 0}, 18, 3.43f, 13.14f},
        {BloonType::Zebra, {0, 0, 0}, 20, 14.29f, 25.14f},
        {BloonType::White, {0, 0, 0}, 10, 27.08f, 32.22f},
        {BloonType::Black, {0, 0, 0}, 10, 32.79f, 37.93f}
    });
    roundTemplates[40] = Round(521, {
        {BloonType::Moab, {0, 0, 0}, 1, 0.50f, 0.50f}
    });
    roundTemplates[41] = Round(2181, {
        {BloonType::Zebra, {0, 0, 0}, 60, 0.00f, 27.36f},
        {BloonType::Black, {0, 0, 0}, 60, 27.43f, 46.20f}
    });
    roundTemplates[42] = Round(659, {
        {BloonType::Rainbow, {0, 1, 0}, 5, 0.00f, 5.00f},
        {BloonType::Rainbow, {0, 0, 0}, 6, 6.60f, 11.60f}
    });
    roundTemplates[43] = Round(1278, {
        {BloonType::Ceramic, {0, 0, 0}, 7, 0.00f, 5.71f},
        {BloonType::Rainbow, {0, 0, 0}, 10, 4.13f, 9.26f}
    });
    roundTemplates[44] = Round(1294, {
        {BloonType::Zebra, {0, 0, 0}, 10, 0.00f, 1.00f},
        {BloonType::Zebra, {0, 0, 0}, 10, 0.92f, 2.92f},
        {BloonType::Zebra, {0, 0, 0}, 10, 2.83f, 6.83f},
        {BloonType::Zebra, {0, 0, 0}, 10, 6.75f, 13.75f},
        {BloonType::Zebra, {0, 0, 0}, 10, 13.67f, 23.67f}
    });
    roundTemplates[45] = Round(2422, {
        {BloonType::Lead, {1, 0, 0}, 4, 0.00f, 2.50f},
        {BloonType::Pink, {0, 0, 0}, 180, 0.02f, 35.02f},
        {BloonType::Purple, {0, 0, 0}, 10, 35.75f, 38.75f},
        {BloonType::Rainbow, {0, 0, 0}, 25, 39.40f, 53.10f}
    });
    roundTemplates[46] = Round(716, {
        {BloonType::Ceramic, {1, 0, 0}, 6, 0.00f, 7.00f}
    });
    roundTemplates[47] = Round(1637, {
        {BloonType::Pink, {0, 1, 0}, 70, 0.00f, 18.15f},
        {BloonType::Ceramic, {0, 0, 0}, 12, 18.36f, 24.65f}
    });
    roundTemplates[48] = Round(2843, {
        {BloonType::Ceramic, {1, 0, 0}, 3, 0.00f, 4.00f},
        {BloonType::Rainbow, {0, 0, 0}, 40, 5.18f, 25.18f},
        {BloonType::Purple, {0, 0, 0}, 30, 25.43f, 40.43f},
        {BloonType::Pink, {0, 0, 0}, 40, 40.72f, 55.72f}
    });
    roundTemplates[49] = Round(4758, {
        {BloonType::Rainbow, {0, 0, 0}, 10, 3.48f, 8.62f},
        {BloonType::Rainbow, {0, 0, 0}, 10, 4.76f, 9.90f},
        {BloonType::Zebra, {0, 0, 0}, 20, 17.21f, 20.73f},
        {BloonType::Ceramic, {0, 0, 0}, 18, 27.96f, 34.50f},
        {BloonType::Rainbow, {0, 0, 0}, 10, 40.86f, 46.00f},
        {BloonType::Green, {0, 0, 0}, 343, 0.00f, 50.00f}
    });
    roundTemplates[50] = Round(3016, {
        {BloonType::Moab, {0, 0, 0}, 1, 0.50f, 0.50f},
        {BloonType::Ceramic, {0, 0, 0}, 20, 1.57f, 12.42f},
        {BloonType::Red, {0, 0, 0}, 20, 17.75f, 19.09f},
        {BloonType::Lead, {0, 0, 0}, 8, 21.92f, 25.92f},
        {BloonType::Moab, {0, 0, 0}, 1, 28.48f, 28.48f}
    });
    roundTemplates[51] = Round(1098, {
        {BloonType::Rainbow, {0, 0, 1}, 10, 0.00f, 5.14f},
        {BloonType::Ceramic, {0, 0, 0}, 15, 6.14f, 24.14f}
    });
    roundTemplates[52] = Round(1595, {
        {BloonType::Ceramic, {0, 0, 0}, 5, 0.00f, 2.28f},
        {BloonType::Moab, {0, 0, 0}, 1, 2.35f, 2.35f},
        {BloonType::Ceramic, {0, 0, 0}, 5, 3.43f, 5.71f},
        {BloonType::Moab, {0, 0, 0}, 1, 5.78f, 5.78f},
        {BloonType::Rainbow, {0, 0, 0}, 25, 6.85f, 20.56f}
    });
    roundTemplates[53] = Round(924, {
        {BloonType::Moab, {0, 0, 0}, 1, 3.42f, 3.42f},
        {BloonType::Moab, {0, 0, 0}, 1, 7.43f, 7.43f},
        {BloonType::Moab, {0, 0, 0}, 1, 14.89f, 14.89f},
        {BloonType::Pink, {0, 1, 0}, 80, 0.00f, 35.00f}
    });
    roundTemplates[54] = Round(2197, {
        {BloonType::Moab, {0, 0, 0}, 1, 6.92f, 6.92f},
        {BloonType::Moab, {0, 0, 0}, 1, 12.68f, 12.68f},
        {BloonType::Ceramic, {0, 0, 0}, 35, 0.00f, 19.41f}
    });
    roundTemplates[55] = Round(2483, {
        {BloonType::Moab, {0, 0, 0}, 1, 0.50f, 0.50f},
        {BloonType::Ceramic, {0, 0, 0}, 15, 6.71f, 7.62f},
        {BloonType::Ceramic, {0, 0, 0}, 10, 13.90f, 15.37f},
        {BloonType::Ceramic, {0, 0, 0}, 10, 20.48f, 21.95f},
        {BloonType::Ceramic, {0, 0, 0}, 10, 28.62f, 29.78f}
    });
    roundTemplates[56] = Round(1286, {
        {BloonType::Moab, {0, 0, 0}, 1, 0.50f, 0.50f},
        {BloonType::Rainbow, {0, 0, 0}, 40, 4.18f, 16.18f}
    });
    roundTemplates[57] = Round(1859, {
        {BloonType::Moab, {0, 0, 0}, 2, 13.10f, 13.67f},
        {BloonType::Rainbow, {0, 0, 0}, 40, 0.00f, 25.26f},
        {BloonType::Moab, {0, 0, 0}, 2, 25.66f, 26.23f}
    });
    roundTemplates[58] = Round(2298, {
        {BloonType::Ceramic, {0, 0, 0}, 10, 0.45f, 20.45f},
        {BloonType::Moab, {0, 0, 0}, 5, 0.00f, 43.98f},
        {BloonType::Ceramic, {0, 0, 0}, 15, 21.98f, 43.98f}
    });
    roundTemplates[59] = Round(2159, {
        {BloonType::Ceramic, {0, 0, 1}, 10, 0.00f, 8.00f},
        {BloonType::Lead, {0, 0, 0}, 50, 8.54f, 15.99f},
        {BloonType::Ceramic, {0, 0, 0}, 20, 16.16f, 26.16f}
    });
    roundTemplates[60] = Round(922, {
        {BloonType::Bfb, {0, 0, 0}, 1, 0.50f, 0.50f}
    });
    roundTemplates[61] = Round(1232, {
        {BloonType::Moab, {0, 0, 0}, 5, 4.05f, 18.08f},
        {BloonType::Zebra, {0, 0, 1}, 150, 0.00f, 20.00f}
    });
    roundTemplates[62] = Round(1386, {
        {BloonType::Rainbow, {0, 1, 0}, 15, 0.00f, 7.99f},
        {BloonType::Moab, {0, 0, 0}, 2, 11.15f, 16.15f},
        {BloonType::Moab, {0, 0, 0}, 5, 27.21f, 47.21f},
        {BloonType::Purple, {0, 0, 0}, 250, 8.29f, 48.29f}
    });
    roundTemplates[63] = Round(2826, {
        {BloonType::Ceramic, {0, 0, 0}, 42, 5.64f, 5.84f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 21.97f, 22.17f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 38.17f, 38.37f},
        {BloonType::Lead, {0, 0, 0}, 75, 0.00f, 42.25f}
    });
    roundTemplates[64] = Round(849, {
        {BloonType::Moab, {1, 0, 0}, 3, 0.00f, 4.00f},
        {BloonType::Moab, {0, 0, 0}, 6, 5.53f, 9.53f}
    });
    roundTemplates[65] = Round(3071, {
        {BloonType::Bfb, {0, 0, 0}, 2, 0.00f, 2.00f},
        {BloonType::Moab, {0, 0, 0}, 3, 2.86f, 3.43f},
        {BloonType::Ceramic, {0, 0, 0}, 50, 3.83f, 14.68f},
        {BloonType::Rainbow, {0, 0, 0}, 70, 15.10f, 29.40f},
        {BloonType::Zebra, {0, 0, 0}, 100, 29.64f, 62.00f}
    });
    roundTemplates[66] = Round(1004, {
        {BloonType::Moab, {1, 0, 0}, 3, 0.00f, 2.00f},
        {BloonType::Moab, {0, 0, 0}, 4, 7.83f, 8.83f},
        {BloonType::Moab, {0, 0, 0}, 2, 15.25f, 15.75f},
        {BloonType::Moab, {0, 0, 0}, 2, 22.25f, 22.75f}
    });
    roundTemplates[67] = Round(1023, {
        {BloonType::Moab, {0, 0, 0}, 4, 0.00f, 2.28f},
        {BloonType::Ceramic, {0, 0, 1}, 13, 9.35f, 17.34f},
        {BloonType::Moab, {0, 0, 0}, 4, 24.15f, 26.44f}
    });
    roundTemplates[68] = Round(777, {
        {BloonType::Bfb, {0, 0, 0}, 1, 0.50f, 0.50f},
        {BloonType::Moab, {0, 0, 0}, 4, 6.73f, 8.44f}
    });
    roundTemplates[69] = Round(1391, {
        {BloonType::Ceramic, {0, 0, 0}, 50, 0.00f, 25.00f},
        {BloonType::Black, {0, 0, 0}, 40, 26.67f, 36.67f},
        {BloonType::Lead, {0, 0, 0}, 40, 25.57f, 42.13f}
    });
    roundTemplates[70] = Round(2618, {
        {BloonType::Moab, {0, 0, 0}, 4, 0.00f, 1.14f},
        {BloonType::Rainbow, {0, 0, 0}, 200, 1.14f, 41.14f},
        {BloonType::White, {0, 0, 0}, 120, 3.14f, 41.14f}
    });
    roundTemplates[71] = Round(1503, {
        {BloonType::Moab, {0, 0, 0}, 10, 7.13f, 12.13f},
        {BloonType::Ceramic, {0, 0, 0}, 30, 0.00f, 16.55f}
    });
    roundTemplates[72] = Round(1504, {
        {BloonType::Bfb, {0, 0, 0}, 1, 5.33f, 5.33f},
        {BloonType::Bfb, {0, 0, 0}, 1, 18.03f, 18.03f},
        {BloonType::Ceramic, {0, 0, 1}, 38, 0.00f, 21.70f}
    });
    roundTemplates[73] = Round(1392, {
        {BloonType::Moab, {0, 0, 0}, 1, 0.29f, 0.29f},
        {BloonType::Bfb, {0, 0, 0}, 2, 10.55f, 13.55f},
        {BloonType::Moab, {0, 0, 0}, 7, 24.67f, 26.95f}
    });
    roundTemplates[74] = Round(3044, {
        {BloonType::Ceramic, {1, 0, 0}, 60, 0.00f, 27.52f},
        {BloonType::Bfb, {0, 0, 0}, 1, 38.21f, 38.21f},
        {BloonType::Ceramic, {1, 0, 0}, 25, 41.24f, 61.24f},
        {BloonType::Ceramic, {0, 0, 0}, 50, 62.38f, 82.39f}
    });
    roundTemplates[75] = Round(2667, {
        {BloonType::Bfb, {0, 0, 0}, 3, 0.00f, 0.10f},
        {BloonType::Moab, {0, 0, 0}, 2, 1.32f, 4.32f},
        {BloonType::Lead, {0, 0, 0}, 14, 4.89f, 12.31f},
        {BloonType::Bfb, {0, 0, 0}, 3, 12.78f, 12.88f},
        {BloonType::Moab, {0, 0, 0}, 1, 13.58f, 13.58f},
        {BloonType::Lead, {0, 0, 0}, 14, 14.59f, 22.02f},
        {BloonType::Bfb, {0, 0, 0}, 1, 22.54f, 22.54f}
    });
    roundTemplates[76] = Round(1316, {
        {BloonType::Ceramic, {0, 0, 1}, 60, 0.00f, 1.78f}
    });
    roundTemplates[77] = Round(2540, {
        {BloonType::Bfb, {0, 0, 0}, 5, 27.70f, 32.25f},
        {BloonType::Moab, {0, 0, 0}, 11, 0.00f, 58.92f}
    });
    roundTemplates[78] = Round(4862, {
        {BloonType::Ceramic, {0, 0, 0}, 72, 10.88f, 12.08f},
        {BloonType::Purple, {0, 0, 0}, 80, 10.60f, 25.60f},
        {BloonType::Bfb, {0, 0, 0}, 1, 45.06f, 45.06f},
        {BloonType::Ceramic, {0, 0, 0}, 75, 78.83f, 80.00f},
        {BloonType::Rainbow, {0, 0, 0}, 150, 0.00f, 90.00f}
    });
    roundTemplates[79] = Round(6709, {
        {BloonType::Bfb, {0, 0, 0}, 2, 2.78f, 12.78f},
        {BloonType::Bfb, {0, 0, 0}, 4, 21.83f, 56.83f},
        {BloonType::Rainbow, {0, 0, 1}, 500, 0.00f, 60.00f}
    });
    roundTemplates[80] = Round(1400, {
        {BloonType::Zomg, {0, 0, 0}, 1, 1.00f, 1.00f}
    });
    roundTemplates[81] = Round(5366, {
        {BloonType::Bfb, {0, 0, 0}, 8, 0.00f, 5.00f},
        {BloonType::Bfb, {0, 0, 0}, 9, 6.47f, 26.47f}
    });
    roundTemplates[82] = Round(4757, {
        {BloonType::Bfb, {1, 0, 0}, 5, 0.00f, 14.00f},
        {BloonType::Bfb, {0, 0, 0}, 10, 15.68f, 35.68f}
    });
    roundTemplates[83] = Round(4749, {
        {BloonType::Moab, {0, 0, 0}, 30, 25.26f, 35.26f},
        {BloonType::Ceramic, {1, 0, 0}, 40, 0.00f, 60.00f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 0.10f, 60.10f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 0.20f, 60.20f}
    });
    roundTemplates[84] = Round(7044, {
        {BloonType::Bfb, {0, 0, 0}, 10, 0.00f, 20.00f},
        {BloonType::Moab, {0, 0, 0}, 50, 0.00f, 25.00f}
    });
    roundTemplates[85] = Round(2625, {
        {BloonType::Zomg, {0, 0, 0}, 2, 0.00f, 10.00f}
    });
    roundTemplates[86] = Round(948, {
        {BloonType::Bfb, {1, 0, 0}, 5, -0.15f, 20.85f}
    });
    roundTemplates[87] = Round(2627, {
        {BloonType::Zomg, {0, 0, 0}, 4, 0.00f, 10.00f}
    });
    roundTemplates[88] = Round(3314, {
        {BloonType::Zomg, {0, 0, 0}, 2, 0.00f, 3.00f},
        {BloonType::Moab, {0, 0, 0}, 18, 3.71f, 8.71f},
        {BloonType::Bfb, {0, 0, 0}, 8, 9.55f, 14.55f}
    });
    roundTemplates[89] = Round(2171, {
        {BloonType::Bfb, {1, 0, 0}, 8, 0.00f, 10.00f},
        {BloonType::Moab, {0, 0, 0}, 20, 10.74f, 20.74f}
    });
    roundTemplates[90] = Round(339, {
        {BloonType::Ddt, {0, 1, 0}, 3, 0.00f, 1.50f},
        {BloonType::Lead, {0, 0, 1}, 50, 1.90f, 11.90f}
    });
    roundTemplates[91] = Round(4191, {
        {BloonType::Bfb, {0, 0, 0}, 20, 12.62f, 22.62f},
        {BloonType::Ceramic, {1, 0, 0}, 100, 0.00f, 30.00f}
    });
    roundTemplates[92] = Round(4537, {
        {BloonType::Zomg, {0, 0, 0}, 4, 16.04f, 22.04f},
        {BloonType::Moab, {1, 0, 0}, 50, 0.00f, 35.00f}
    });
    roundTemplates[93] = Round(1946, {
        {BloonType::Ddt, {0, 1, 0}, 6, 5.65f, 7.65f},
        {BloonType::Bfb, {1, 0, 0}, 10, 0.00f, 20.00f}
    });
    roundTemplates[94] = Round(7667, {
        {BloonType::Zomg, {0, 0, 0}, 6, 0.39f, 13.39f},
        {BloonType::Bfb, {0, 0, 0}, 25, 0.00f, 15.00f}
    });
    roundTemplates[95] = Round(3718, {
        {BloonType::Moab, {1, 0, 0}, 50, 0.00f, 20.00f},
        {BloonType::Ddt, {0, 1, 0}, 30, 0.00f, 20.00f},
        {BloonType::Purple, {0, 0, 0}, 500, 20.81f, 50.81f},
        {BloonType::Lead, {0, 0, 0}, 250, 20.81f, 50.81f}
    });
    roundTemplates[96] = Round(9955, {
        {BloonType::Zomg, {0, 0, 0}, 6, 0.00f, 5.00f},
        {BloonType::Bfb, {0, 0, 0}, 10, 5.50f, 10.50f},
        {BloonType::Moab, {0, 0, 0}, 20, 11.08f, 16.08f},
        {BloonType::Bfb, {0, 0, 0}, 10, 16.38f, 21.38f},
        {BloonType::Moab, {0, 0, 0}, 20, 21.62f, 26.62f},
        {BloonType::Bfb, {0, 0, 0}, 10, 27.12f, 32.12f}
    });
    roundTemplates[97] = Round(1417, {
        {BloonType::Zomg, {1, 0, 0}, 2, 0.00f, 5.00f}
    });
    roundTemplates[98] = Round(9653, {
        {BloonType::Bfb, {1, 0, 0}, 30, 0.00f, 30.00f},
        {BloonType::Zomg, {0, 0, 0}, 8, 25.00f, 30.00f}
    });
    roundTemplates[99] = Round(2827, {
        {BloonType::Ddt, {1, 1, 0}, 9, 0.49f, 5.49f},
        {BloonType::Moab, {0, 0, 0}, 60, 0.00f, 12.00f}
    });
    roundTemplates[100] = Round(1534, {
        {BloonType::Bad, {0, 0, 0}, 1, 0.05f, 0.05f}
    });
}

const Round& ReverseRoundSpawner::getRound(int roundNumber) const {
    // Find the round for the given round number
    auto it = roundTemplates.find(roundNumber);
    if (it != roundTemplates.end()) {
        return it->second;
    }

    // Should not be there
    std::cerr << "Round number not found: " << roundNumber << std::endl;
    return roundTemplates.at(1); // Return the first round as a fallback
}