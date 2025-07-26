#include "AlternativeRoundSpawner.h"
#include <iostream>

AlternativeRoundSpawner::AlternativeRoundSpawner() {
    init();
}

void AlternativeRoundSpawner::init() {
    // Initialize the round templates for different rounds
    
        roundTemplates[1] = Round(121, {
        {BloonType::Blue, {0, 0, 0}, 10, 0.00f, 23.00f}
    });
    roundTemplates[2] = Round(157, {
        {BloonType::Red, {0, 0, 0}, 35, 0.00f, 15.00f},
        {BloonType::Red, {0, 0, 0}, 20, 18.00f, 25.00f}
    });
    roundTemplates[3] = Round(140, {
        {BloonType::Blue, {0, 0, 0}, 6, 0.00f, 5.10f},
        {BloonType::Blue, {0, 0, 0}, 5, 5.70f, 7.95f},
        {BloonType::Red, {0, 0, 0}, 15, 9.71f, 16.71f}
    });
    roundTemplates[4] = Round(180, {
        {BloonType::Blue, {0, 0, 0}, 15, 0.00f, 12.00f},
        {BloonType::Blue, {0, 0, 0}, 18, 7.90f, 10.40f},
        {BloonType::Red, {0, 0, 0}, 10, 14.51f, 17.31f}
    });
    roundTemplates[5] = Round(157, {
        {BloonType::Red, {0, 1, 0}, 12, 0.00f, 5.14f},
        {BloonType::Green, {0, 0, 0}, 3, 5.70f, 7.98f},
        {BloonType::Blue, {0, 0, 0}, 15, 8.60f, 16.50f},
        {BloonType::Red, {0, 0, 0}, 1, 19.40f, 19.40f}
    });
    roundTemplates[6] = Round(165, {
        {BloonType::Green, {0, 0, 0}, 8, 0.00f, 3.00f},
        {BloonType::Blue, {0, 0, 0}, 10, 5.33f, 10.33f},
        {BloonType::Green, {0, 0, 0}, 5, 10.80f, 18.70f}
    });
    roundTemplates[7] = Round(197, {
        {BloonType::Black, {0, 0, 0}, 2, 0.00f, 5.14f},
        {BloonType::Green, {0, 0, 0}, 6, 5.70f, 10.65f},
        {BloonType::Blue, {0, 0, 0}, 15, 11.81f, 22.65f},
        {BloonType::Blue, {0, 0, 0}, 10, 22.81f, 26.80f}
    });
    roundTemplates[8] = Round(193, {
        {BloonType::Yellow, {0, 0, 0}, 10, 0.00f, 10.84f},
        {BloonType::Green, {0, 0, 0}, 3, 11.42f, 11.99f},
        {BloonType::Green, {0, 0, 0}, 12, 13.00f, 28.00f}
    });
    roundTemplates[9] = Round(199, {
        {BloonType::Green, {0, 0, 1}, 30, 0.00f, 18.95f}
    });
    roundTemplates[10] = Round(320, {
        {BloonType::Green, {0, 0, 0}, 40, 0.00f, 35.00f},
        {BloonType::Lead, {0, 0, 0}, 2, 35.00f, 39.00f},
        {BloonType::Blue, {0, 0, 0}, 22, 40.17f, 44.16f}
    });
    roundTemplates[11] = Round(220, {
        {BloonType::Green, {0, 1, 0}, 3, 0.00f, 1.00f},
        {BloonType::Green, {0, 0, 0}, 20, 4.47f, 10.75f},
        {BloonType::Blue, {0, 0, 0}, 10, 10.87f, 14.67f},
        {BloonType::Blue, {0, 0, 0}, 10, 14.59f, 19.16f}
    });
    roundTemplates[12] = Round(185, {
        {BloonType::Green, {0, 0, 1}, 6, 0.00f, 5.13f},
        {BloonType::Blue, {0, 0, 0}, 20, 5.70f, 12.70f},
        {BloonType::Pink, {0, 0, 0}, 3, 14.27f, 17.39f}
    });
    roundTemplates[13] = Round(285, {
        {BloonType::Blue, {0, 0, 0}, 50, 0.00f, 30.00f},
        {BloonType::Yellow, {0, 0, 0}, 18, 2.21f, 32.21f}
    });
    roundTemplates[14] = Round(258, {
        {BloonType::Red, {0, 0, 0}, 18, 0.00f, 9.71f},
        {BloonType::Black, {0, 0, 0}, 1, 3.41f, 3.41f},
        {BloonType::White, {0, 0, 0}, 1, 6.27f, 6.27f},
        {BloonType::Yellow, {0, 0, 0}, 4, 8.56f, 9.51f},
        {BloonType::Red, {0, 0, 0}, 31, 9.50f, 26.63f},
        {BloonType::Blue, {0, 0, 0}, 10, 15.96f, 17.34f},
        {BloonType::Green, {0, 0, 0}, 5, 19.84f, 21.22f},
        {BloonType::Black, {0, 0, 0}, 2, 23.71f, 25.26f}
    });
    roundTemplates[15] = Round(331, {
        {BloonType::Blue, {0, 0, 0}, 20, 0.00f, 25.00f},
        {BloonType::Green, {0, 0, 0}, 15, 2.78f, 22.78f},
        {BloonType::Yellow, {0, 0, 0}, 12, 5.68f, 20.68f},
        {BloonType::Pink, {0, 0, 0}, 10, 8.87f, 20.87f},
        {BloonType::Purple, {0, 0, 0}, 3, 17.55f, 20.55f}
    });
    roundTemplates[16] = Round(281, {
        {BloonType::Green, {0, 0, 1}, 20, 0.00f, 10.85f},
        {BloonType::Green, {0, 0, 0}, 20, 0.20f, 11.05f},
        {BloonType::Green, {0, 0, 0}, 15, 14.59f, 16.02f}
    });
    roundTemplates[17] = Round(177, {
        {BloonType::Pink, {0, 0, 0}, 12, 0.00f, 5.00f}
    });
    roundTemplates[18] = Round(448, {
        {BloonType::Yellow, {0, 0, 0}, 60, 0.00f, 25.00f},
        {BloonType::Green, {0, 0, 0}, 30, 25.00f, 26.82f}
    });
    roundTemplates[19] = Round(251, {
        {BloonType::Blue, {0, 0, 0}, 10, 0.00f, 2.89f},
        {BloonType::Green, {0, 0, 0}, 5, 2.85f, 5.19f},
        {BloonType::Pink, {0, 0, 0}, 15, 5.96f, 13.57f},
        {BloonType::Black, {0, 0, 0}, 2, 13.48f, 15.76f}
    });
    roundTemplates[20] = Round(186, {
        {BloonType::Black, {0, 0, 1}, 6, 0.00f, 5.25f}
    });
    roundTemplates[21] = Round(179, {
        {BloonType::Red, {0, 0, 0}, 40, 0.09f, 10.09f},
        {BloonType::Red, {0, 0, 0}, 10, 10.84f, 15.98f},
        {BloonType::Blue, {0, 0, 0}, 4, 16.68f, 18.12f}
    });
    roundTemplates[22] = Round(298, {
        {BloonType::Purple, {0, 0, 0}, 16, 0.00f, 8.00f}
    });
    roundTemplates[23] = Round(358, {
        {BloonType::Black, {0, 0, 0}, 7, 0.00f, 2.50f},
        {BloonType::White, {0, 0, 0}, 6, 4.82f, 6.82f},
        {BloonType::Lead, {0, 0, 0}, 4, 7.00f, 9.00f}
    });
    roundTemplates[24] = Round(147, {
        {BloonType::Lead, {0, 1, 0}, 1, 0.50f, 0.50f}
    });
    roundTemplates[25] = Round(345, {
        {BloonType::Pink, {0, 0, 1}, 22, 0.00f, 14.00f},
        {BloonType::Purple, {0, 0, 0}, 10, 17.14f, 21.14f}
    });
    roundTemplates[26] = Round(454, {
        {BloonType::Black, {0, 0, 0}, 15, 0.00f, 8.70f},
        {BloonType::Zebra, {0, 0, 0}, 3, 11.08f, 14.51f},
        {BloonType::Rainbow, {0, 0, 0}, 2, 15.20f, 18.20f}
    });
    roundTemplates[27] = Round(662, {
        {BloonType::Red, {0, 1, 0}, 100, 0.02f, 12.02f},
        {BloonType::Blue, {0, 0, 0}, 60, 11.54f, 19.54f},
        {BloonType::Green, {0, 0, 0}, 45, 19.05f, 26.40f},
        {BloonType::Yellow, {0, 0, 0}, 45, 26.53f, 34.26f}
    });
    roundTemplates[28] = Round(266, {
        {BloonType::Lead, {0, 0, 1}, 6, 0.00f, 5.00f}
    });
    roundTemplates[29] = Round(467, {
        {BloonType::Pink, {0, 0, 1}, 50, 0.00f, 11.00f},
        {BloonType::White, {0, 0, 0}, 8, 12.75f, 15.25f}
    });
    roundTemplates[30] = Round(337, {
        {BloonType::Lead, {0, 1, 0}, 9, 0.00f, 13.07f}
    });
    roundTemplates[31] = Round(606, {
        {BloonType::Black, {0, 0, 1}, 8, 0.00f, 5.09f},
        {BloonType::White, {0, 0, 0}, 8, 0.35f, 5.44f},
        {BloonType::Zebra, {0, 0, 0}, 10, 6.16f, 11.25f},
        {BloonType::Zebra, {0, 0, 0}, 3, 13.00f, 14.71f}
    });
    roundTemplates[32] = Round(762, {
        {BloonType::Rainbow, {0, 0, 0}, 5, 0.00f, 9.00f},
        {BloonType::Ceramic, {0, 0, 0}, 3, 10.34f, 19.34f},
        {BloonType::Purple, {0, 0, 0}, 10, 20.00f, 26.00f}
    });
    roundTemplates[33] = Round(179, {
        {BloonType::Red, {0, 1, 0}, 20, 0.00f, 5.00f},
        {BloonType::Blue, {0, 0, 0}, 13, 5.34f, 25.34f}
    });
    roundTemplates[34] = Round(1016, {
        {BloonType::Green, {0, 0, 0}, 200, 0.00f, 36.00f},
        {BloonType::Rainbow, {0, 0, 0}, 6, 8.62f, 26.70f}
    });
    roundTemplates[35] = Round(1300, {
        {BloonType::White, {0, 0, 1}, 25, 0.00f, 10.03f},
        {BloonType::Ceramic, {0, 0, 0}, 3, 14.35f, 16.64f},
        {BloonType::Purple, {0, 0, 0}, 25, 19.21f, 26.21f},
        {BloonType::Black, {0, 0, 0}, 30, 26.76f, 33.76f}
    });
    roundTemplates[36] = Round(756, {
        {BloonType::Yellow, {0, 1, 0}, 40, 0.00f, 1.51f},
        {BloonType::Black, {0, 0, 0}, 5, 4.01f, 5.36f},
        {BloonType::Yellow, {0, 0, 0}, 40, 8.49f, 9.84f},
        {BloonType::Black, {0, 0, 0}, 5, 12.67f, 14.02f},
        {BloonType::Ceramic, {0, 0, 0}, 2, 16.99f, 18.99f}
    });
    roundTemplates[37] = Round(1408, {
        {BloonType::White, {0, 0, 1}, 25, 0.00f, 10.85f},
        {BloonType::White, {0, 0, 0}, 25, 11.42f, 22.27f},
        {BloonType::Lead, {0, 0, 0}, 18, 22.84f, 30.83f},
        {BloonType::Zebra, {0, 0, 0}, 10, 31.40f, 36.54f},
        {BloonType::Black, {0, 0, 0}, 7, 41.92f, 43.51f}
    });
    roundTemplates[38] = Round(1533, {
        {BloonType::Black, {0, 0, 0}, 17, 0.00f, 3.60f},
        {BloonType::Purple, {0, 0, 0}, 42, 2.00f, 25.41f},
        {BloonType::Lead, {0, 0, 0}, 14, 4.83f, 13.40f},
        {BloonType::Rainbow, {0, 0, 0}, 7, 12.09f, 18.37f},
        {BloonType::Ceramic, {0, 0, 0}, 1, 28.06f, 28.06f}
    });
    roundTemplates[39] = Round(1508, {
        {BloonType::White, {0, 1, 0}, 10, 0.00f, 5.14f},
        {BloonType::Zebra, {0, 0, 0}, 5, 5.71f, 10.85f},
        {BloonType::Zebra, {0, 0, 0}, 15, 12.79f, 23.64f},
        {BloonType::Rainbow, {0, 0, 0}, 15, 24.79f, 34.50f},
        {BloonType::Rainbow, {0, 0, 0}, 2, 35.93f, 37.93f}
    });
    roundTemplates[40] = Round(521, {
        {BloonType::Moab, {1, 0, 0}, 1, 0.50f, 0.50f}
    });
    roundTemplates[41] = Round(2411, {
        {BloonType::Black, {0, 0, 0}, 60, 0.00f, 18.77f},
        {BloonType::Zebra, {0, 0, 0}, 70, 10.00f, 32.00f}
    });
    roundTemplates[42] = Round(659, {
        {BloonType::Rainbow, {0, 1, 0}, 6, 0.00f, 5.00f},
        {BloonType::Rainbow, {0, 0, 1}, 5, 6.60f, 10.60f}
    });
    roundTemplates[43] = Round(1375, {
        {BloonType::Rainbow, {0, 0, 0}, 10, 0.00f, 5.14f},
        {BloonType::Moab, {0, 0, 0}, 2, 3.55f, 9.26f}
    });
    roundTemplates[44] = Round(1294, {
        {BloonType::Zebra, {0, 0, 0}, 10, 0.00f, 10.00f},
        {BloonType::Lead, {0, 0, 0}, 10, 9.92f, 16.92f},
        {BloonType::Zebra, {0, 0, 0}, 10, 16.83f, 20.83f},
        {BloonType::Zebra, {0, 0, 0}, 10, 20.75f, 22.75f},
        {BloonType::Zebra, {0, 0, 0}, 10, 22.67f, 23.67f}
    });
    roundTemplates[45] = Round(1897, {
        {BloonType::Ceramic, {0, 0, 0}, 10, 0.00f, 13.70f},
        {BloonType::Purple, {0, 0, 0}, 10, 14.35f, 17.35f},
        {BloonType::Pink, {0, 0, 0}, 120, 18.08f, 38.08f},
        {BloonType::Lead, {0, 0, 0}, 4, 35.00f, 37.50f}
    });
    roundTemplates[46] = Round(906, {
        {BloonType::Ceramic, {1, 0, 0}, 8, 0.00f, 7.00f}
    });
    roundTemplates[47] = Round(1640, {
        {BloonType::Moab, {0, 0, 0}, 3, 0.00f, 6.28f},
        {BloonType::Pink, {0, 0, 1}, 70, 6.50f, 24.65f}
    });
    roundTemplates[48] = Round(1988, {
        {BloonType::Lead, {0, 0, 1}, 15, 0.00f, 15.00f},
        {BloonType::Purple, {0, 0, 1}, 30, 15.29f, 30.29f},
        {BloonType::Black, {0, 0, 0}, 80, 30.54f, 50.54f},
        {BloonType::Ceramic, {0, 0, 0}, 3, 48.00f, 52.00f}
    });
    roundTemplates[49] = Round(3849, {
        {BloonType::Yellow, {0, 0, 1}, 300, 0.00f, 50.00f},
        {BloonType::Rainbow, {0, 0, 0}, 10, 4.00f, 9.14f},
        {BloonType::Ceramic, {0, 0, 0}, 14, 15.50f, 22.04f},
        {BloonType::Zebra, {0, 0, 0}, 10, 40.10f, 45.24f},
        {BloonType::Rainbow, {0, 0, 0}, 10, 41.38f, 46.52f}
    });
    roundTemplates[50] = Round(2620, {
        {BloonType::Moab, {1, 0, 0}, 2, 0.00f, 3.00f},
        {BloonType::Lead, {1, 0, 0}, 8, 3.06f, 7.06f},
        {BloonType::Moab, {0, 0, 0}, 4, 13.00f, 18.00f}
    });
    roundTemplates[51] = Round(1596, {
        {BloonType::Ceramic, {0, 1, 0}, 28, 0.00f, 15.42f},
        {BloonType::Zebra, {0, 0, 0}, 10, 15.99f, 21.13f}
    });
    roundTemplates[52] = Round(1830, {
        {BloonType::Rainbow, {0, 0, 0}, 35, 0.00f, 13.70f},
        {BloonType::Moab, {0, 0, 0}, 1, 14.77f, 14.77f},
        {BloonType::Ceramic, {0, 0, 0}, 5, 14.85f, 17.13f},
        {BloonType::Moab, {0, 0, 0}, 1, 18.20f, 18.20f},
        {BloonType::Ceramic, {0, 0, 0}, 5, 18.27f, 20.56f}
    });
    roundTemplates[53] = Round(1024, {
        {BloonType::Pink, {0, 1, 0}, 120, 0.00f, 35.00f},
        {BloonType::Moab, {0, 0, 0}, 1, 20.11f, 20.11f},
        {BloonType::Moab, {0, 0, 0}, 1, 27.57f, 27.57f},
        {BloonType::Moab, {0, 0, 0}, 1, 31.58f, 31.58f}
    });
    roundTemplates[54] = Round(1299, {
        {BloonType::Black, {0, 0, 1}, 35, 0.00f, 19.41f},
        {BloonType::Moab, {0, 0, 0}, 1, 6.73f, 6.73f},
        {BloonType::Bfb, {0, 0, 0}, 1, 12.49f, 12.49f}
    });
    roundTemplates[55] = Round(2483, {
        {BloonType::Ceramic, {0, 0, 0}, 10, 0.00f, 1.16f},
        {BloonType::Ceramic, {0, 0, 0}, 10, 7.83f, 9.30f},
        {BloonType::Ceramic, {0, 0, 0}, 10, 14.42f, 15.89f},
        {BloonType::Ceramic, {0, 0, 0}, 15, 22.17f, 23.07f},
        {BloonType::Moab, {0, 0, 0}, 1, 29.28f, 29.28f}
    });
    roundTemplates[56] = Round(1328, {
        {BloonType::Purple, {0, 1, 0}, 40, 0.00f, 12.00f},
        {BloonType::Moab, {0, 0, 0}, 5, 15.18f, 20.18f}
    });
    roundTemplates[57] = Round(2488, {
        {BloonType::Moab, {1, 0, 0}, 2, 0.00f, 0.57f},
        {BloonType::Ceramic, {0, 0, 0}, 25, 0.97f, 26.23f},
        {BloonType::Bfb, {0, 0, 0}, 1, 12.85f, 12.85f}
    });
    roundTemplates[58] = Round(3250, {
        {BloonType::Ceramic, {0, 0, 0}, 15, 0.00f, 22.00f},
        {BloonType::Moab, {0, 0, 0}, 10, 0.00f, 43.98f},
        {BloonType::Ceramic, {0, 0, 0}, 10, 23.53f, 43.53f}
    });
    roundTemplates[59] = Round(2271, {
        {BloonType::Ceramic, {0, 1, 0}, 20, 0.00f, 10.00f},
        {BloonType::Lead, {0, 0, 1}, 50, 10.17f, 17.62f},
        {BloonType::Rainbow, {0, 0, 0}, 25, 18.16f, 26.16f}
    });
    roundTemplates[60] = Round(922, {
        {BloonType::Bfb, {1, 0, 0}, 1, 0.50f, 0.50f}
    });
    roundTemplates[61] = Round(1603, {
        {BloonType::Zebra, {0, 0, 1}, 50, 0.00f, 10.00f},
        {BloonType::Moab, {0, 0, 0}, 15, 1.92f, 15.95f},
        {BloonType::Lead, {0, 0, 0}, 15, 10.34f, 24.37f}
    });
    roundTemplates[62] = Round(1772, {
        {BloonType::Purple, {0, 0, 0}, 250, 0.00f, 40.00f},
        {BloonType::Moab, {0, 0, 0}, 5, 1.08f, 21.08f},
        {BloonType::Bfb, {0, 0, 0}, 2, 32.14f, 37.14f},
        {BloonType::Lead, {0, 0, 0}, 15, 40.30f, 48.29f}
    });
    roundTemplates[63] = Round(2634, {
        {BloonType::Ceramic, {1, 0, 0}, 30, 0.00f, 42.25f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 3.88f, 4.08f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 20.08f, 20.28f},
        {BloonType::Moab, {0, 0, 0}, 5, 36.42f, 36.62f}
    });
    roundTemplates[64] = Round(1231, {
        {BloonType::Moab, {1, 0, 0}, 6, 0.00f, 4.00f},
        {BloonType::Bfb, {0, 0, 0}, 2, 5.53f, 9.53f}
    });
    roundTemplates[65] = Round(2916, {
        {BloonType::Bfb, {0, 0, 0}, 3, 0.00f, 15.00f},
        {BloonType::Rainbow, {0, 0, 0}, 70, 15.24f, 29.55f},
        {BloonType::Ceramic, {0, 0, 0}, 50, 29.81f, 40.66f},
        {BloonType::Moab, {0, 0, 0}, 3, 39.64f, 40.21f}
    });
    roundTemplates[66] = Round(1538, {
        {BloonType::Bfb, {0, 0, 0}, 1, 0.25f, 0.25f},
        {BloonType::Moab, {0, 0, 0}, 2, 7.00f, 7.50f},
        {BloonType::Moab, {0, 0, 0}, 4, 13.92f, 14.92f},
        {BloonType::Bfb, {0, 0, 0}, 2, 20.75f, 23.75f}
    });
    roundTemplates[67] = Round(1309, {
        {BloonType::Moab, {1, 0, 0}, 4, 0.00f, 2.28f},
        {BloonType::Ceramic, {0, 0, 1}, 20, 9.10f, 17.09f},
        {BloonType::Moab, {0, 0, 0}, 6, 24.15f, 26.44f}
    });
    roundTemplates[68] = Round(777, {
        {BloonType::Moab, {0, 0, 0}, 4, 0.00f, 1.71f},
        {BloonType::Bfb, {0, 0, 0}, 1, 7.94f, 7.94f}
    });
    roundTemplates[69] = Round(1295, {
        {BloonType::Purple, {0, 1, 0}, 40, 0.00f, 16.56f},
        {BloonType::Black, {0, 0, 1}, 40, 5.46f, 15.46f},
        {BloonType::Ceramic, {0, 0, 0}, 50, 17.13f, 42.13f}
    });
    roundTemplates[70] = Round(2507, {
        {BloonType::Rainbow, {0, 0, 0}, 200, 0.00f, 30.00f},
        {BloonType::Moab, {0, 0, 0}, 6, 18.89f, 20.89f}
    });
    roundTemplates[71] = Round(1503, {
        {BloonType::Ceramic, {0, 0, 1}, 30, 0.00f, 16.55f},
        {BloonType::Moab, {0, 0, 0}, 10, 4.42f, 9.42f}
    });
    roundTemplates[72] = Round(1504, {
        {BloonType::Ceramic, {1, 0, 0}, 38, 0.00f, 21.70f},
        {BloonType::Bfb, {0, 0, 0}, 1, 3.67f, 3.67f},
        {BloonType::Bfb, {0, 0, 0}, 1, 16.37f, 16.37f}
    });
    roundTemplates[73] = Round(1392, {
        {BloonType::Moab, {1, 0, 0}, 7, 0.00f, 2.28f},
        {BloonType::Bfb, {0, 0, 0}, 2, 13.40f, 17.40f},
        {BloonType::Moab, {0, 0, 0}, 1, 26.67f, 26.67f}
    });
    roundTemplates[74] = Round(1174, {
        {BloonType::Black, {0, 0, 1}, 100, 0.00f, 15.00f},
        {BloonType::Ceramic, {0, 0, 1}, 25, 15.41f, 30.41f},
        {BloonType::Bfb, {0, 0, 0}, 1, 31.19f, 31.19f}
    });
    roundTemplates[75] = Round(3214, {
        {BloonType::Bfb, {0, 0, 0}, 1, 0.05f, 0.05f},
        {BloonType::Lead, {0, 0, 0}, 50, 0.57f, 7.99f},
        {BloonType::Bfb, {0, 0, 0}, 5, 9.25f, 9.35f},
        {BloonType::Lead, {0, 0, 0}, 14, 10.28f, 17.70f},
        {BloonType::Moab, {0, 0, 0}, 4, 18.27f, 21.27f},
        {BloonType::Bfb, {0, 0, 0}, 2, 22.49f, 22.59f}
    });
    roundTemplates[76] = Round(3226, {
        {BloonType::Bfb, {0, 0, 0}, 10, 0.00f, 10.00f}
    });
    roundTemplates[77] = Round(2540, {
        {BloonType::Moab, {1, 0, 0}, 11, 0.00f, 58.92f},
        {BloonType::Bfb, {0, 0, 0}, 5, 26.67f, 36.67f}
    });
    roundTemplates[78] = Round(3857, {
        {BloonType::Zebra, {0, 0, 0}, 150, 0.00f, 60.00f},
        {BloonType::Ceramic, {0, 0, 0}, 60, 10.00f, 11.17f},
        {BloonType::Bfb, {0, 0, 0}, 1, 44.94f, 44.94f},
        {BloonType::Purple, {0, 0, 0}, 80, 64.40f, 79.40f},
        {BloonType::Ceramic, {0, 0, 0}, 72, 77.92f, 79.12f}
    });
    roundTemplates[79] = Round(7319, {
        {BloonType::Rainbow, {0, 1, 0}, 500, 0.00f, 60.00f},
        {BloonType::Bfb, {0, 0, 0}, 4, 3.17f, 38.17f},
        {BloonType::Zomg, {0, 0, 0}, 1, 48.72f, 48.72f}
    });
    roundTemplates[80] = Round(2620, {
        {BloonType::Zomg, {0, 0, 0}, 2, 0.00f, 20.00f}
    });
    roundTemplates[81] = Round(6280, {
        {BloonType::Bfb, {0, 0, 0}, 15, 0.00f, 20.00f},
        {BloonType::Moab, {0, 0, 0}, 20, 21.47f, 26.47f}
    });
    roundTemplates[82] = Round(8417, {
        {BloonType::Bfb, {0, 0, 0}, 15, 0.00f, 20.00f},
        {BloonType::Bfb, {0, 0, 0}, 8, 21.68f, 35.68f},
        {BloonType::Zomg, {0, 0, 0}, 1, 37.05f, 37.05f}
    });
    roundTemplates[83] = Round(3987, {
        {BloonType::Ceramic, {0, 1, 0}, 40, 0.00f, 60.00f},
        {BloonType::Ceramic, {0, 0, 0}, 40, 0.10f, 60.10f},
        {BloonType::Ceramic, {1, 0, 0}, 40, 0.20f, 60.20f},
        {BloonType::Moab, {0, 0, 0}, 20, 24.94f, 34.94f}
    });
    roundTemplates[84] = Round(8569, {
        {BloonType::Moab, {0, 0, 0}, 50, 0.00f, 25.00f},
        {BloonType::Bfb, {0, 0, 0}, 15, 5.00f, 35.00f}
    });
    roundTemplates[85] = Round(3845, {
        {BloonType::Zomg, {0, 0, 0}, 3, 0.00f, 10.00f}
    });
    roundTemplates[86] = Round(1406, {
        {BloonType::Bfb, {1, 0, 0}, 8, -0.15f, 20.85f}
    });
    roundTemplates[87] = Round(3237, {
        {BloonType::Zomg, {0, 0, 0}, 5, 0.00f, 10.00f}
    });
    roundTemplates[88] = Round(2703, {
        {BloonType::Bfb, {0, 0, 0}, 12, 0.00f, 5.00f},
        {BloonType::Moab, {0, 0, 0}, 15, 5.84f, 10.84f},
        {BloonType::Ddt, {0, 0, 0}, 3, 11.55f, 13.05f}
    });
    roundTemplates[89] = Round(2590, {
        {BloonType::Moab, {1, 0, 0}, 15, 0.00f, 7.00f},
        {BloonType::Bfb, {0, 0, 0}, 12, 8.15f, 18.15f}
    });
    roundTemplates[90] = Round(817, {
        {BloonType::Ceramic, {0, 0, 1}, 50, 0.00f, 10.00f},
        {BloonType::Ddt, {0, 0, 0}, 4, 10.40f, 11.90f}
    });
    roundTemplates[91] = Round(3428, {
        {BloonType::Ceramic, {1, 0, 0}, 100, 0.00f, 30.00f},
        {BloonType::Bfb, {0, 0, 0}, 15, 7.38f, 17.38f}
    });
    roundTemplates[92] = Round(4689, {
        {BloonType::Moab, {1, 0, 0}, 50, 0.00f, 35.00f},
        {BloonType::Zomg, {0, 0, 0}, 4, 12.96f, 18.96f},
        {BloonType::Ddt, {0, 0, 0}, 4, 22.23f, 23.23f}
    });
    roundTemplates[93] = Round(3052, {
        {BloonType::Bfb, {1, 0, 0}, 17, 0.00f, 20.00f},
        {BloonType::Ddt, {1, 0, 0}, 7, 6.79f, 8.79f}
    });
    roundTemplates[94] = Round(8887, {
        {BloonType::Bfb, {0, 0, 0}, 25, 0.00f, 15.00f},
        {BloonType::Zomg, {0, 0, 0}, 8, 1.61f, 14.61f}
    });
    roundTemplates[95] = Round(2781, {
        {BloonType::Purple, {0, 1, 0}, 500, 0.00f, 30.00f},
        {BloonType::Ddt, {0, 0, 0}, 30, 17.82f, 37.82f},
        {BloonType::Moab, {0, 0, 0}, 30, 30.81f, 40.81f}
    });
    roundTemplates[96] = Round(11100, {
        {BloonType::Bfb, {1, 0, 0}, 10, 0.00f, 5.00f},
        {BloonType::Moab, {0, 0, 0}, 20, 5.50f, 10.50f},
        {BloonType::Zomg, {0, 0, 0}, 5, 10.74f, 15.74f},
        {BloonType::Ddt, {0, 0, 0}, 10, 16.04f, 21.04f},
        {BloonType::Bfb, {0, 0, 0}, 10, 21.62f, 26.62f},
        {BloonType::Zomg, {0, 0, 0}, 6, 27.12f, 32.12f}
    });
    roundTemplates[97] = Round(1722, {
        {BloonType::Zomg, {1, 0, 0}, 2, 0.00f, 4.00f},
        {BloonType::Ddt, {1, 0, 0}, 8, 1.23f, 4.23f}
    });
    roundTemplates[98] = Round(9959, {
        {BloonType::Bfb, {1, 0, 0}, 20, 0.00f, 20.00f},
        {BloonType::Zomg, {0, 0, 0}, 11, 0.00f, 5.00f}
    });
    roundTemplates[99] = Round(3019, {
        {BloonType::Moab, {0, 0, 0}, 30, 0.00f, 12.00f},
        {BloonType::Ddt, {1, 0, 0}, 9, 6.51f, 11.51f},
        {BloonType::Bad, {0, 0, 0}, 1, 16.78f, 16.78f}
    });
    roundTemplates[100] = Round(1534, {
        {BloonType::Bad, {1, 0, 0}, 1, 0.05f, 0.05f}
    });

}

const Round& AlternativeRoundSpawner::getRound(int roundNumber) const {
    // Find the round for the given round number
    auto it = roundTemplates.find(roundNumber);
    if (it != roundTemplates.end()) {
        return it->second;
    }

    // Should not be there
    std::cerr << "Round number not found: " << roundNumber << std::endl;
    return roundTemplates.at(1); // Return the first round as a fallback
}