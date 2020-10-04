#include "tiledexport.h"

const std::array<vec, 1401> TiledEntities::obstacle = {
	vec(-2500.5f, -408.834f),
	vec(-2490.5f, -423.583f),
	vec(-2471.75f, -433.333f),
	vec(-2453.5f, -444.583f),
	vec(-2433.25f, -455.583f),
	vec(-2417.75f, -468.083f),
	vec(-2398.75f, -479.083f),
	vec(-2382.67f, -490.25f),
	vec(-2366.17f, -498.75f),
	vec(-2345.42f, -508.5f),
	vec(-2326.42f, -517.25f),
	vec(-2304.17f, -524.25f),
	vec(-2285.08f, -536.083f),
	vec(-2265.33f, -541.833f),
	vec(-2242.83f, -546.083f),
	vec(-2225.0f, -554.667f),
	vec(-2202.5f, -559.417f),
	vec(-2182.5f, -561.417f),
	vec(-2162.25f, -562.417f),
	vec(-2140.5f, -563.417f),
	vec(-2121.5f, -564.167f),
	vec(-2104.25f, -564.167f),
	vec(-2086.25f, -565.417f),
	vec(-2067.5f, -565.667f),
	vec(-2044.5f, -567.917f),
	vec(-2026.0f, -568.667f),
	vec(-2004.5f, -568.167f),
	vec(-1986.25f, -568.667f),
	vec(-1966.88f, -569.042f),
	vec(-1947.88f, -567.792f),
	vec(-1930.63f, -567.792f),
	vec(-1912.5f, -568.042f),
	vec(-1893.75f, -568.292f),
	vec(-1876.75f, -567.542f),
	vec(-1858.25f, -568.292f),
	vec(-1836.75f, -567.792f),
	vec(-1818.5f, -568.292f),
	vec(-1798.94f, -567.741f),
	vec(-1780.21f, -568.354f),
	vec(-1761.46f, -568.604f),
	vec(-1744.46f, -567.854f),
	vec(-1725.96f, -568.604f),
	vec(-1704.46f, -568.104f),
	vec(-1686.21f, -568.604f),
	vec(-1666.84f, -568.979f),
	vec(-1647.84f, -568.729f),
	vec(-1630.59f, -568.729f),
	vec(-1612.46f, -568.979f),
	vec(-1593.71f, -568.229f),
	vec(-1576.71f, -567.479f),
	vec(-1558.21f, -568.229f),
	vec(-1895.67f, -437.032f),
	vec(-1876.67f, -437.782f),
	vec(-1859.42f, -437.782f),
	vec(-1841.29f, -438.032f),
	vec(-1822.54f, -438.282f),
	vec(-1805.54f, -437.532f),
	vec(-1787.04f, -438.282f),
	vec(-1765.54f, -437.782f),
	vec(-1747.29f, -438.282f),
	vec(-1727.73f, -437.731f),
	vec(-1709.0f, -438.344f),
	vec(-1690.25f, -438.594f),
	vec(-1673.25f, -437.844f),
	vec(-1654.75f, -438.594f),
	vec(-1633.25f, -438.094f),
	vec(-1615.0f, -438.594f),
	vec(-1595.63f, -438.969f),
	vec(-1576.63f, -438.719f),
	vec(-1559.38f, -438.719f),
	vec(-1541.25f, -438.969f),
	vec(-1522.5f, -438.219f),
	vec(-1505.5f, -437.469f),
	vec(-1487.0f, -438.219f),
	vec(-2100.25f, -435.844f),
	vec(-2081.75f, -436.594f),
	vec(-2060.25f, -436.094f),
	vec(-2042.0f, -436.594f),
	vec(-2022.63f, -436.969f),
	vec(-2003.63f, -436.719f),
	vec(-1986.38f, -436.719f),
	vec(-1968.25f, -436.969f),
	vec(-1949.5f, -436.219f),
	vec(-1932.5f, -437.469f),
	vec(-1914.0f, -437.219f),
	vec(-2403.38f, -279.333f),
	vec(-2230.13f, -394.333f),
	vec(-2214.38f, -404.333f),
	vec(-2196.13f, -413.333f),
	vec(-2178.38f, -419.333f),
	vec(-2160.88f, -426.833f),
	vec(-2141.13f, -429.583f),
	vec(-2121.13f, -433.333f),
	vec(-2388.34f, -293.709f),
	vec(-2376.16f, -306.292f),
	vec(-2360.91f, -319.542f),
	vec(-2342.66f, -331.792f),
	vec(-2322.41f, -342.792f),
	vec(-2299.91f, -354.292f),
	vec(-2283.91f, -365.292f),
	vec(-2263.16f, -374.792f),
	vec(-2246.66f, -383.292f),
	vec(-2415.0f, -264.0f),
	vec(-2428.0f, -246.5f),
	vec(-2437.5f, -230.0f),
	vec(-2449.0f, -211.333f),
	vec(-2457.33f, -192.667f),
	vec(-2463.83f, -175.167f),
	vec(-2473.83f, -156.167f),
	vec(-2477.83f, -135.167f),
	vec(-2479.83f, -113.167f),
	vec(-2481.33f, -93.1667f),
	vec(-2480.83f, -72.1667f),
	vec(-2480.83f, -52.1667f),
	vec(-2482.33f, -32.0f),
	vec(-2481.66f, -12.6667f),
	vec(-2476.33f, 6.66666f),
	vec(-2477.67f, 29.3333f),
	vec(-2466.33f, 48.6667f),
	vec(-2460.67f, 68.0f),
	vec(-2450.67f, 85.3333f),
	vec(-2440.67f, 103.333f),
	vec(-2424.33f, 122.0f),
	vec(-2405.67f, 138.667f),
	vec(-2388.33f, 152.333f),
	vec(-2371.0f, 164.667f),
	vec(-2352.67f, 178.667f),
	vec(-2333.0f, 187.0f),
	vec(-2315.0f, 197.667f),
	vec(-2296.33f, 205.333f),
	vec(-2277.33f, 213.667f),
	vec(-2259.33f, 222.0f),
	vec(-2241.67f, 230.0f),
	vec(-2223.0f, 236.333f),
	vec(-2203.0f, 243.667f),
	vec(-2184.67f, 253.0f),
	vec(-2166.0f, 261.667f),
	vec(-2147.33f, 271.0f),
	vec(-2129.67f, 280.667f),
	vec(-2111.67f, 288.667f),
	vec(-2094.67f, 298.667f),
	vec(-2078.33f, 312.333f),
	vec(-2516.83f, -399.167f),
	vec(-2532.83f, -385.667f),
	vec(-2541.17f, -370.667f),
	vec(-2556.67f, -354.167f),
	vec(-2569.67f, -336.167f),
	vec(-2580.67f, -317.167f),
	vec(-2590.17f, -299.667f),
	vec(-2596.0f, -278.0f),
	vec(-2603.0f, -256.5f),
	vec(-2638.5f, 51.3333f),
	vec(-2635.0f, 75.3333f),
	vec(-2630.5f, 100.333f),
	vec(-2621.0f, 124.833f),
	vec(-2609.83f, 147.0f),
	vec(-2600.33f, 169.0f),
	vec(-2589.83f, 190.5f),
	vec(-2577.83f, 212.5f),
	vec(-2564.83f, 230.5f),
	vec(-2549.33f, 248.0f),
	vec(-2538.83f, 269.5f),
	vec(-2524.83f, 283.0f),
	vec(-2508.0f, 293.5f),
	vec(-2492.5f, 308.5f),
	vec(-2471.5f, 321.0f),
	vec(-2452.0f, 332.0f),
	vec(-2433.0f, 343.5f),
	vec(-2413.5f, 356.0f),
	vec(-2396.5f, 370.5f),
	vec(-2376.5f, 382.5f),
	vec(-2356.0f, 391.0f),
	vec(-2339.0f, 395.5f),
	vec(-2319.0f, 406.0f),
	vec(-2304.0f, 414.0f),
	vec(-2286.0f, 421.5f),
	vec(-2270.0f, 426.0f),
	vec(-2253.33f, 434.667f),
	vec(-2241.17f, 442.667f),
	vec(-2222.0f, 451.0f),
	vec(-2198.33f, 473.667f),
	vec(-2188.5f, 491.667f),
	vec(-2183.17f, 508.833f),
	vec(-2176.67f, 527.667f),
	vec(-2169.17f, 547.667f),
	vec(-2166.17f, 570.167f),
	vec(-2162.34f, 589.334f),
	vec(-2158.67f, 607.167f),
	vec(-2157.67f, 626.167f),
	vec(-2149.67f, 647.667f),
	vec(-2142.67f, 665.167f),
	vec(-2133.67f, 684.667f),
	vec(-2126.67f, 704.167f),
	vec(-2114.67f, 722.167f),
	vec(-2102.67f, 740.667f),
	vec(-2082.17f, 751.667f),
	vec(-2063.67f, 764.167f),
	vec(-2043.33f, 771.0f),
	vec(-2023.0f, 778.0f),
	vec(-2002.33f, 786.0f),
	vec(-1981.33f, 789.0f),
	vec(-2068.5f, 331.5f),
	vec(-2058.0f, 352.5f),
	vec(-2047.0f, 373.0f),
	vec(-2040.0f, 394.5f),
	vec(-2035.0f, 412.5f),
	vec(-2033.0f, 435.0f),
	vec(-2028.0f, 457.0f),
	vec(-2026.5f, 477.5f),
	vec(-2025.0f, 497.0f),
	vec(-2023.0f, 516.5f),
	vec(-2019.5f, 537.0f),
	vec(-2013.0f, 556.0f),
	vec(-2008.0f, 574.0f),
	vec(-1999.5f, 591.0f),
	vec(-1990.5f, 609.0f),
	vec(-1957.75f, 622.25f),
	vec(-1938.25f, 625.5f),
	vec(-1917.25f, 625.25f),
	vec(-1958.25f, 793.917f),
	vec(-1936.92f, 794.25f),
	vec(-1915.33f, 794.75f),
	vec(-1893.08f, 792.167f),
	vec(-1871.92f, 792.5f),
	vec(-1852.83f, 790.833f),
	vec(-1842.75f, 627.354f),
	vec(-1823.75f, 626.604f),
	vec(-1806.5f, 626.604f),
	vec(-1788.37f, 626.354f),
	vec(-1769.62f, 626.104f),
	vec(-1752.62f, 626.854f),
	vec(-1734.12f, 626.104f),
	vec(-1712.62f, 626.604f),
	vec(-1694.37f, 626.104f),
	vec(-1674.81f, 626.655f),
	vec(-1656.08f, 626.042f),
	vec(-1637.33f, 625.792f),
	vec(-1620.33f, 626.542f),
	vec(-1601.83f, 625.792f),
	vec(-1580.33f, 626.292f),
	vec(-1562.08f, 625.792f),
	vec(-1542.71f, 625.417f),
	vec(-1523.71f, 625.667f),
	vec(-1506.46f, 625.667f),
	vec(-1488.33f, 625.417f),
	vec(-1469.58f, 626.167f),
	vec(-1452.58f, 626.917f),
	vec(-1434.08f, 626.167f),
	vec(-1896.58f, 627.167f),
	vec(-1879.58f, 627.917f),
	vec(-1861.08f, 627.167f),
	vec(-1781.92f, 789.187f),
	vec(-1762.92f, 788.437f),
	vec(-1745.67f, 788.437f),
	vec(-1727.54f, 788.187f),
	vec(-1708.79f, 787.937f),
	vec(-1691.79f, 788.687f),
	vec(-1673.29f, 787.937f),
	vec(-1651.79f, 788.437f),
	vec(-1633.54f, 787.937f),
	vec(-1613.98f, 788.488f),
	vec(-1595.25f, 787.875f),
	vec(-1576.5f, 787.625f),
	vec(-1559.5f, 788.375f),
	vec(-1541.0f, 787.625f),
	vec(-1519.5f, 788.125f),
	vec(-1501.25f, 787.625f),
	vec(-1481.88f, 787.25f),
	vec(-1462.88f, 787.5f),
	vec(-1445.63f, 787.5f),
	vec(-1427.5f, 787.25f),
	vec(-1408.75f, 788.0f),
	vec(-1391.75f, 788.75f),
	vec(-1373.25f, 788.0f),
	vec(-1835.75f, 789.0f),
	vec(-1818.75f, 789.75f),
	vec(-1800.25f, 789.0f),
	vec(-1360.92f, 624.187f),
	vec(-1341.92f, 623.437f),
	vec(-1324.67f, 623.437f),
	vec(-1306.54f, 623.187f),
	vec(-1287.79f, 622.937f),
	vec(-1270.79f, 623.687f),
	vec(-1252.29f, 622.937f),
	vec(-1230.79f, 623.437f),
	vec(-1212.54f, 622.937f),
	vec(-1192.98f, 623.488f),
	vec(-1174.25f, 622.875f),
	vec(-1155.5f, 622.625f),
	vec(-1138.5f, 623.375f),
	vec(-1120.0f, 622.625f),
	vec(-1098.5f, 623.125f),
	vec(-1080.25f, 622.625f),
	vec(-1060.88f, 622.25f),
	vec(-1041.88f, 622.5f),
	vec(-1024.63f, 622.5f),
	vec(-1006.5f, 622.25f),
	vec(-987.75f, 623.0f),
	vec(-970.75f, 623.75f),
	vec(-952.25f, 623.0f),
	vec(-1414.75f, 624.0f),
	vec(-1397.75f, 624.75f),
	vec(-1379.25f, 624.0f),
	vec(-1301.42f, 787.687f),
	vec(-1282.42f, 786.937f),
	vec(-1265.17f, 786.937f),
	vec(-1247.04f, 786.687f),
	vec(-1228.29f, 786.437f),
	vec(-1211.29f, 787.187f),
	vec(-1192.79f, 786.437f),
	vec(-1171.29f, 786.937f),
	vec(-1153.04f, 786.437f),
	vec(-1133.48f, 786.988f),
	vec(-1114.75f, 786.375f),
	vec(-1096.0f, 786.125f),
	vec(-1079.0f, 786.875f),
	vec(-1060.5f, 786.125f),
	vec(-1039.0f, 786.625f),
	vec(-1020.75f, 786.125f),
	vec(-1001.38f, 785.75f),
	vec(-982.38f, 786.0f),
	vec(-965.13f, 786.0f),
	vec(-947.0f, 785.75f),
	vec(-928.25f, 786.5f),
	vec(-911.25f, 787.25f),
	vec(-892.75f, 786.5f),
	vec(-1355.25f, 787.5f),
	vec(-1338.25f, 788.25f),
	vec(-1319.75f, 787.5f),
	vec(-820.92f, 787.687f),
	vec(-801.92f, 786.937f),
	vec(-784.67f, 786.937f),
	vec(-766.54f, 786.687f),
	vec(-747.79f, 786.437f),
	vec(-730.79f, 787.187f),
	vec(-712.29f, 786.437f),
	vec(-690.79f, 786.937f),
	vec(-672.54f, 786.437f),
	vec(-652.98f, 786.988f),
	vec(-634.25f, 786.375f),
	vec(-615.5f, 786.125f),
	vec(-598.5f, 786.875f),
	vec(-580.0f, 786.125f),
	vec(-558.5f, 786.625f),
	vec(-540.25f, 786.125f),
	vec(-520.88f, 785.75f),
	vec(-501.88f, 786.0f),
	vec(-484.63f, 786.0f),
	vec(-466.5f, 785.75f),
	vec(-447.75f, 786.5f),
	vec(-430.75f, 787.25f),
	vec(-412.25f, 786.5f),
	vec(-874.75f, 787.5f),
	vec(-857.75f, 788.25f),
	vec(-839.25f, 787.5f),
	vec(-881.92f, 622.187f),
	vec(-862.92f, 621.437f),
	vec(-845.67f, 621.437f),
	vec(-827.54f, 621.187f),
	vec(-808.79f, 620.937f),
	vec(-791.79f, 621.687f),
	vec(-773.29f, 620.937f),
	vec(-751.79f, 621.437f),
	vec(-733.54f, 620.937f),
	vec(-713.98f, 621.488f),
	vec(-695.25f, 620.875f),
	vec(-676.5f, 620.625f),
	vec(-659.5f, 621.375f),
	vec(-641.0f, 620.625f),
	vec(-619.5f, 621.125f),
	vec(-601.25f, 620.625f),
	vec(-581.88f, 620.25f),
	vec(-562.88f, 620.5f),
	vec(-545.63f, 620.5f),
	vec(-527.5f, 620.25f),
	vec(-508.75f, 621.0f),
	vec(-491.75f, 621.75f),
	vec(-473.25f, 621.0f),
	vec(-935.75f, 622.0f),
	vec(-918.75f, 622.75f),
	vec(-900.25f, 622.0f),
	vec(-338.42f, 785.687f),
	vec(-319.42f, 784.937f),
	vec(-302.17f, 784.937f),
	vec(-284.04f, 784.687f),
	vec(-265.29f, 784.437f),
	vec(-248.29f, 785.187f),
	vec(-229.79f, 784.437f),
	vec(-208.29f, 784.937f),
	vec(-190.04f, 784.437f),
	vec(-170.48f, 784.988f),
	vec(-151.75f, 784.375f),
	vec(-133.0f, 784.125f),
	vec(-116.0f, 784.875f),
	vec(-97.5f, 784.125f),
	vec(-76.0f, 784.625f),
	vec(-57.75f, 784.125f),
	vec(-38.38f, 783.75f),
	vec(-19.38f, 784.0f),
	vec(-2.13f, 784.0f),
	vec(16.0f, 783.75f),
	vec(34.75f, 784.5f),
	vec(51.75f, 785.25f),
	vec(70.25f, 784.5f),
	vec(-392.25f, 785.5f),
	vec(-375.25f, 786.25f),
	vec(-356.75f, 785.5f),
	vec(-401.92f, 621.187f),
	vec(-382.92f, 620.437f),
	vec(-365.67f, 620.437f),
	vec(-347.54f, 620.187f),
	vec(-328.79f, 619.937f),
	vec(-311.79f, 620.687f),
	vec(-293.29f, 619.937f),
	vec(-271.79f, 620.437f),
	vec(-253.54f, 619.937f),
	vec(-233.98f, 620.488f),
	vec(-215.25f, 619.875f),
	vec(-196.5f, 619.625f),
	vec(-179.5f, 620.375f),
	vec(-161.0f, 619.625f),
	vec(-139.5f, 620.125f),
	vec(-121.25f, 619.625f),
	vec(-101.88f, 619.25f),
	vec(-82.88f, 619.5f),
	vec(-65.63f, 619.5f),
	vec(-47.5f, 619.25f),
	vec(-28.75f, 620.0f),
	vec(-11.75f, 620.75f),
	vec(6.75f, 620.0f),
	vec(-455.75f, 621.0f),
	vec(-438.75f, 621.75f),
	vec(-420.25f, 621.0f),
	vec(79.08f, 619.687f),
	vec(98.08f, 618.937f),
	vec(115.33f, 618.937f),
	vec(133.46f, 618.687f),
	vec(152.21f, 618.437f),
	vec(169.21f, 619.187f),
	vec(187.71f, 618.437f),
	vec(209.21f, 618.937f),
	vec(227.46f, 618.437f),
	vec(247.02f, 618.988f),
	vec(265.75f, 618.375f),
	vec(284.5f, 618.125f),
	vec(301.5f, 618.875f),
	vec(320.0f, 618.125f),
	vec(341.5f, 618.625f),
	vec(359.75f, 618.125f),
	vec(379.12f, 617.75f),
	vec(398.12f, 618.0f),
	vec(415.37f, 618.0f),
	vec(433.5f, 617.75f),
	vec(452.25f, 618.5f),
	vec(469.25f, 619.25f),
	vec(487.75f, 618.5f),
	vec(25.25f, 619.5f),
	vec(42.25f, 620.25f),
	vec(60.75f, 619.5f),
	vec(142.58f, 784.187f),
	vec(161.58f, 783.437f),
	vec(178.83f, 783.437f),
	vec(196.96f, 783.187f),
	vec(215.71f, 782.937f),
	vec(232.71f, 783.687f),
	vec(251.21f, 782.937f),
	vec(272.71f, 783.437f),
	vec(290.96f, 782.937f),
	vec(310.52f, 783.488f),
	vec(329.25f, 782.875f),
	vec(348.0f, 782.625f),
	vec(365.0f, 783.375f),
	vec(383.5f, 782.625f),
	vec(405.0f, 783.125f),
	vec(423.25f, 782.625f),
	vec(442.62f, 782.25f),
	vec(461.62f, 782.5f),
	vec(478.87f, 782.5f),
	vec(497.0f, 782.25f),
	vec(515.75f, 783.0f),
	vec(532.75f, 783.75f),
	vec(551.25f, 783.0f),
	vec(88.75f, 784.0f),
	vec(105.75f, 784.75f),
	vec(124.25f, 784.0f),
	vec(624.58f, 782.687f),
	vec(643.58f, 781.937f),
	vec(660.83f, 781.937f),
	vec(678.96f, 781.687f),
	vec(697.71f, 781.437f),
	vec(714.71f, 782.187f),
	vec(733.21f, 781.437f),
	vec(754.71f, 781.937f),
	vec(772.96f, 781.437f),
	vec(792.52f, 781.988f),
	vec(811.25f, 781.375f),
	vec(830.0f, 781.125f),
	vec(847.0f, 781.875f),
	vec(865.5f, 781.125f),
	vec(887.0f, 781.625f),
	vec(905.25f, 781.125f),
	vec(924.62f, 780.75f),
	vec(943.62f, 781.0f),
	vec(960.87f, 781.0f),
	vec(979.0f, 780.75f),
	vec(997.75f, 781.5f),
	vec(1014.75f, 782.25f),
	vec(1033.25f, 781.5f),
	vec(570.75f, 782.5f),
	vec(587.75f, 783.25f),
	vec(606.25f, 782.5f),
	vec(560.58f, 617.687f),
	vec(579.58f, 616.937f),
	vec(596.83f, 616.937f),
	vec(614.96f, 616.687f),
	vec(633.71f, 616.437f),
	vec(650.71f, 617.187f),
	vec(669.21f, 616.437f),
	vec(690.71f, 616.937f),
	vec(708.96f, 616.437f),
	vec(728.52f, 616.988f),
	vec(747.25f, 616.375f),
	vec(766.0f, 616.125f),
	vec(783.0f, 616.875f),
	vec(801.5f, 616.125f),
	vec(823.0f, 616.625f),
	vec(841.25f, 616.125f),
	vec(860.62f, 615.75f),
	vec(879.62f, 616.0f),
	vec(896.87f, 616.0f),
	vec(915.0f, 615.75f),
	vec(933.75f, 616.5f),
	vec(950.75f, 617.25f),
	vec(969.25f, 616.5f),
	vec(506.75f, 617.5f),
	vec(523.75f, 618.25f),
	vec(542.25f, 617.5f),
	vec(1050.5f, 777.0f),
	vec(1068.5f, 770.5f),
	vec(1108.0f, 765.0f),
	vec(1128.33f, 757.333f),
	vec(1149.33f, 746.167f),
	vec(1172.83f, 733.167f),
	vec(1194.67f, 723.167f),
	vec(1212.0f, 715.167f),
	vec(1230.5f, 703.167f),
	vec(1248.5f, 689.5f),
	vec(1262.0f, 676.5f),
	vec(1272.5f, 660.0f),
	vec(1290.83f, 643.0f),
	vec(1300.5f, 625.0f),
	vec(1312.5f, 606.0f),
	vec(1328.5f, 590.5f),
	vec(1336.0f, 571.5f),
	vec(1338.5f, 552.0f),
	vec(986.5f, 612.0f),
	vec(1006.5f, 606.0f),
	vec(1027.0f, 594.5f),
	vec(1043.5f, 583.0f),
	vec(1066.0f, 570.0f),
	vec(1083.0f, 555.5f),
	vec(1100.0f, 543.5f),
	vec(1118.0f, 527.5f),
	vec(1133.5f, 514.0f),
	vec(1149.0f, 498.0f),
	vec(1166.0f, 482.0f),
	vec(1176.5f, 464.0f),
	vec(1179.5f, 443.0f),
	vec(1179.0f, 424.0f),
	vec(1182.5f, 405.5f),
	vec(1181.0f, 384.0f),
	vec(1182.0f, 364.5f),
	vec(1182.5f, 343.5f),
	vec(1183.0f, 324.5f),
	vec(1186.0f, 303.5f),
	vec(1187.5f, 281.5f),
	vec(1187.5f, 262.5f),
	vec(1188.5f, 240.0f),
	vec(1186.5f, 223.0f),
	vec(1170.0f, 211.5f),
	vec(1151.5f, 201.5f),
	vec(1134.0f, 195.0f),
	vec(1114.0f, 186.0f),
	vec(1097.5f, 175.0f),
	vec(1089.5f, 157.5f),
	vec(1089.91f, 107.091f),
	vec(1091.82f, 89.2727f),
	vec(1093.05f, 72.0f),
	vec(1363.67f, 135.167f),
	vec(1349.0f, 124.167f),
	vec(1334.67f, 114.5f),
	vec(1316.17f, 105.334f),
	vec(1300.33f, 99.3337f),
	vec(1283.17f, 92.3334f),
	vec(1277.67f, 76.3334f),
	vec(-1977.0f, 621.25f),
	vec(1093.75f, 55.5f),
	vec(1095.25f, 35.5f),
	vec(1096.25f, 13.5f),
	vec(1098.75f, -6.5f),
	vec(1103.13f, -29.25f),
	vec(1103.63f, -49.25f),
	vec(1104.88f, -69.75f),
	vec(1106.38f, -89.75f),
	vec(1107.38f, -111.75f),
	vec(1109.88f, -131.75f),
	vec(1111.63f, -151.75f),
	vec(1112.13f, -171.75f),
	vec(1113.38f, -192.25f),
	vec(1114.88f, -212.25f),
	vec(1115.08f, -372.75f),
	vec(1099.5f, -222.0f),
	vec(1083.5f, -230.5f),
	vec(1067.0f, -238.0f),
	vec(1051.0f, -242.5f),
	vec(1032.5f, -249.5f),
	vec(1014.0f, -258.0f),
	vec(998.5f, -264.0f),
	vec(980.0f, -267.0f),
	vec(964.0f, -274.5f),
	vec(947.5f, -282.0f),
	vec(931.5f, -286.5f),
	vec(913.0f, -293.5f),
	vec(893.5f, -301.0f),
	vec(876.0f, -306.0f),
	vec(858.5f, -308.75f),
	vec(840.0f, -315.75f),
	vec(821.5f, -324.25f),
	vec(801.5f, -332.083f),
	vec(785.0f, -339.583f),
	vec(769.0f, -344.083f),
	vec(750.5f, -351.083f),
	vec(731.0f, -358.583f),
	vec(712.5f, -358.083f),
	vec(692.5f, -348.333f),
	vec(1097.58f, -379.625f),
	vec(1081.08f, -387.125f),
	vec(1063.75f, -390.958f),
	vec(1045.25f, -397.958f),
	vec(1026.75f, -406.458f),
	vec(1011.25f, -412.458f),
	vec(996.083f, -415.125f),
	vec(980.083f, -422.625f),
	vec(963.583f, -430.125f),
	vec(947.583f, -434.625f),
	vec(931.833f, -441.375f),
	vec(912.333f, -448.875f),
	vec(894.833f, -452.875f),
	vec(877.333f, -455.625f),
	vec(859.5f, -460.958f),
	vec(841.0f, -465.125f),
	vec(825.5f, -471.125f),
	vec(807.0f, -474.125f),
	vec(791.0f, -481.625f),
	vec(722.5f, -501.458f),
	vec(775.167f, -487.625f),
	vec(757.667f, -492.625f),
	vec(739.417f, -495.75f),
	vec(706.129f, -503.871f),
	vec(672.386f, -504.341f),
	vec(655.705f, -504.295f),
	vec(624.25f, -491.0f),
	vec(-1540.0f, -567.792f),
	vec(-1521.25f, -568.042f),
	vec(-1504.25f, -567.292f),
	vec(-1485.75f, -568.042f),
	vec(-1464.25f, -567.542f),
	vec(-1446.0f, -568.042f),
	vec(-1426.63f, -568.417f),
	vec(-1312.3f, -566.167f),
	vec(-1292.92f, -560.417f),
	vec(-1271.17f, -556.0f),
	vec(-1254.84f, -548.917f),
	vec(-1239.67f, -538.0f),
	vec(-1468.86f, -437.833f),
	vec(-1450.73f, -438.083f),
	vec(-1431.98f, -437.333f),
	vec(-1414.98f, -436.583f),
	vec(-1396.48f, -437.333f),
	vec(-1223.0f, -524.333f),
	vec(-1210.34f, -508.667f),
	vec(-1194.34f, -493.667f),
	vec(-1181.34f, -475.333f),
	vec(-1174.0f, -453.0f),
	vec(-1165.0f, -435.667f),
	vec(-1158.0f, -418.0f),
	vec(-1151.0f, -401.0f),
	vec(-1149.0f, -368.334f),
	vec(-1151.33f, -350.667f),
	vec(-1151.0f, -331.0f),
	vec(-1152.33f, -312.334f),
	vec(-1153.16f, -295.167f),
	vec(-1157.83f, -272.5f),
	vec(-1162.16f, -251.833f),
	vec(-1166.83f, -232.166f),
	vec(-1175.16f, -213.5f),
	vec(-1180.59f, -196.083f),
	vec(-1187.42f, -178.916f),
	vec(-1194.42f, -159.917f),
	vec(-1205.75f, -143.25f),
	vec(-1217.42f, -126.249f),
	vec(-1233.41f, -113.25f),
	vec(-1380.33f, -435.0f),
	vec(-1366.0f, -424.667f),
	vec(-1348.33f, -411.333f),
	vec(-1334.33f, -394.667f),
	vec(-1322.67f, -376.333f),
	vec(-1313.0f, -357.333f),
	vec(-1306.0f, -339.333f),
	vec(-1305.0f, -319.0f),
	vec(-1306.33f, -299.0f),
	vec(-1309.67f, -280.667f),
	vec(-1316.0f, -259.333f),
	vec(-1323.33f, -240.0f),
	vec(-1332.33f, -221.333f),
	vec(-1347.33f, -205.333f),
	vec(-1358.67f, -188.333f),
	vec(-1374.33f, -172.333f),
	vec(-1391.67f, -156.0f),
	vec(-1408.33f, -149.333f),
	vec(-1426.33f, -137.667f),
	vec(-1444.67f, -133.667f),
	vec(-1463.33f, -125.333f),
	vec(-1480.0f, -124.0f),
	vec(-1243.75f, -97.5833f),
	vec(-1254.67f, -83.0f),
	vec(-1270.92f, -68.75f),
	vec(-1289.92f, -58.0f),
	vec(-1305.67f, -43.75f),
	vec(-1324.42f, -30.75f),
	vec(-1343.42f, -23.25f),
	vec(-1496.75f, -124.25f),
	vec(-1515.25f, -124.75f),
	vec(-1535.25f, -125.5f),
	vec(-1555.5f, -124.5f),
	vec(-1574.25f, -124.25f),
	vec(-1596.75f, -124.5f),
	vec(-1616.0f, -123.5f),
	vec(-1634.25f, -122.75f),
	vec(-1357.92f, -17.0f),
	vec(-1373.67f, -10.5f),
	vec(-1388.42f, -4.5f),
	vec(-1406.17f, 2.25f),
	vec(-1421.42f, 3.5f),
	vec(-1440.17f, 3.75f),
	vec(-1459.67f, 4.0f),
	vec(-1651.31f, -124.0f),
	vec(-1669.44f, -125.125f),
	vec(-1687.94f, -125.625f),
	vec(-1707.94f, -126.375f),
	vec(-1728.19f, -125.375f),
	vec(-1746.94f, -125.125f),
	vec(-1769.44f, -125.375f),
	vec(-1788.69f, -124.375f),
	vec(-1806.94f, -123.625f),
	vec(-1829.19f, -124.875f),
	vec(-1846.03f, -124.938f),
	vec(-1868.53f, -125.188f),
	vec(-1887.78f, -124.188f),
	vec(-1906.03f, -123.438f),
	vec(-1923.09f, -124.688f),
	vec(-1941.22f, -125.813f),
	vec(-1959.72f, -126.313f),
	vec(-1979.72f, -127.063f),
	vec(-1999.97f, -126.063f),
	vec(-2018.72f, -125.813f),
	vec(-2041.22f, -126.063f),
	vec(-2060.47f, -125.063f),
	vec(-2078.72f, -124.313f),
	vec(-2100.97f, -120.563f),
	vec(-2039.14f, 24.4375f),
	vec(-2116.75f, -113.5f),
	vec(-2134.25f, -104.0f),
	vec(-2153.0f, -94.5f),
	vec(-2164.75f, -79.25f),
	vec(-2178.25f, -63.25f),
	vec(-2190.75f, -42.0f),
	vec(-2200.25f, -25.5f),
	vec(-2210.5f, -8.25f),
	vec(-2211.25f, 9.25f),
	vec(-2212.0f, 28.0f),
	vec(-2210.0f, 47.25f),
	vec(-2204.75f, 66.0f),
	vec(-2196.75f, 83.75f),
	vec(-2189.5f, 101.25f),
	vec(-2022.17f, 33.75f),
	vec(-2012.42f, 44.75f),
	vec(-1998.17f, 52.0f),
	vec(-2176.5f, 116.25f),
	vec(-2163.75f, 127.75f),
	vec(-1980.92f, 60.875f),
	vec(-1965.67f, 71.875f),
	vec(-2150.5f, 142.625f),
	vec(-2135.25f, 153.625f),
	vec(-2121.0f, 162.875f),
	vec(-2107.0f, 176.688f),
	vec(-2091.25f, 187.188f),
	vec(-2077.0f, 198.063f),
	vec(-2061.75f, 209.063f),
	vec(-2047.5f, 216.313f),
	vec(-2031.75f, 226.906f),
	vec(-2016.5f, 237.906f),
	vec(-2002.25f, 247.156f),
	vec(-1988.25f, 260.969f),
	vec(-1972.5f, 271.469f),
	vec(-1958.25f, 282.344f),
	vec(-1943.0f, 293.344f),
	vec(-1928.75f, 300.594f),
	vec(-1913.0f, 306.906f),
	vec(-1897.75f, 317.906f),
	vec(-1883.5f, 327.156f),
	vec(-1869.5f, 340.969f),
	vec(-1850.75f, 352.469f),
	vec(-1836.5f, 363.344f),
	vec(-1821.25f, 371.344f),
	vec(-1829.08f, 169.323f),
	vec(-1814.83f, 178.573f),
	vec(-1789.5f, 205.052f),
	vec(-1773.75f, 215.552f),
	vec(-1759.5f, 226.427f),
	vec(-1744.25f, 237.427f),
	vec(-1730.0f, 244.677f),
	vec(-1712.0f, 254.989f),
	vec(-1696.75f, 265.989f),
	vec(-1682.5f, 276.573f),
	vec(-1666.5f, 285.386f),
	vec(-1650.75f, 291.886f),
	vec(-1636.5f, 297.761f),
	vec(-1621.25f, 303.761f),
	vec(-1604.0f, 309.011f),
	vec(-1807.92f, 378.609f),
	vec(-1790.17f, 387.109f),
	vec(-1775.92f, 397.984f),
	vec(-1760.67f, 404.984f),
	vec(-1746.42f, 414.234f),
	vec(-1729.67f, 420.827f),
	vec(-1713.42f, 428.827f),
	vec(-1695.83f, 436.744f),
	vec(-1677.83f, 444.557f),
	vec(-1659.08f, 452.39f),
	vec(676.333f, -339.666f),
	vec(662.667f, -327.333f),
	vec(650.0f, -313.0f),
	vec(635.667f, -301.0f),
	vec(623.333f, -285.333f),
	vec(615.167f, -268.0f),
	vec(612.167f, -249.666f),
	vec(612.667f, -233.583f),
	vec(615.667f, -218.0f),
	vec(621.0f, -200.333f),
	vec(626.0f, -182.666f),
	vec(638.0f, -165.666f),
	vec(648.333f, -148.333f),
	vec(664.0f, -136.333f),
	vec(680.333f, -126.0f),
	vec(694.667f, -120.333f),
	vec(711.333f, -111.333f),
	vec(728.667f, -106.666f),
	vec(746.0f, -99.0003f),
	vec(763.333f, -94.0003f),
	vec(780.0f, -86.3333f),
	vec(800.333f, -76.3333f),
	vec(835.0f, -63.6667f),
	vec(844.667f, -45.3333f),
	vec(857.667f, -26.6666f),
	vec(866.0f, -8.0f),
	vec(869.667f, 9.33337f),
	vec(875.0f, 27.0f),
	vec(881.333f, 44.6667f),
	vec(888.667f, 63.3334f),
	vec(894.667f, 79.3334f),
	vec(900.667f, 96.6667f),
	vec(908.0f, 115.0f),
	vec(913.667f, 132.334f),
	vec(923.333f, 149.334f),
	vec(929.333f, 168.667f),
	vec(935.667f, 186.334f),
	vec(942.0f, 202.667f),
	vec(948.667f, 220.0f),
	vec(954.333f, 239.0f),
	vec(961.969f, 258.698f),
	vec(967.515f, 276.394f),
	vec(972.424f, 293.818f),
	vec(977.333f, 311.0f),
	vec(973.333f, 327.667f),
	vec(965.333f, 343.667f),
	vec(956.0f, 359.0f),
	vec(943.333f, 371.667f),
	vec(931.0f, 384.5f),
	vec(913.333f, 392.5f),
	vec(895.833f, 401.0f),
	vec(878.333f, 404.5f),
	vec(860.0f, 406.0f),
	vec(823.5f, 402.0f),
	vec(805.333f, 402.667f),
	vec(786.333f, 396.333f),
	vec(768.333f, 394.0f),
	vec(750.667f, 390.333f),
	vec(733.167f, 386.667f),
	vec(769.833f, 238.833f),
	vec(754.167f, 231.833f),
	vec(737.5f, 225.5f),
	vec(722.5f, 217.167f),
	vec(781.167f, 230.166f),
	vec(773.833f, 213.167f),
	vec(764.167f, 199.167f),
	vec(711.5f, 208.833f),
	vec(698.667f, 199.333f),
	vec(685.0f, 190.333f),
	vec(670.333f, 182.667f),
	vec(756.5f, 183.833f),
	vec(749.5f, 168.167f),
	vec(739.667f, 153.667f),
	vec(733.75f, 133.667f),
	vec(722.333f, 117.583f),
	vec(710.584f, 101.583f),
	vec(700.25f, 85.6667f),
	vec(693.0f, 69.334f),
	vec(682.333f, 53.0f),
	vec(674.0f, 40.834f),
	vec(589.5f, -29.3334f),
	vec(604.167f, -18.6668f),
	vec(620.5f, -11.3334f),
	vec(637.5f, -1.66677f),
	vec(649.167f, 11.0f),
	vec(662.167f, 25.6666f),
	vec(448.5f, -161.666f),
	vec(453.5f, -143.999f),
	vec(459.5f, -126.999f),
	vec(467.833f, -109.666f),
	vec(476.833f, -92.6665f),
	vec(491.5f, -80.6668f),
	vec(505.834f, -72.9998f),
	vec(522.5f, -63.9998f),
	vec(539.834f, -56.3328f),
	vec(557.167f, -49.6668f),
	vec(450.334f, -289.167f),
	vec(445.667f, -269.834f),
	vec(439.667f, -232.167f),
	vec(442.667f, -214.5f),
	vec(443.667f, -197.5f),
	vec(446.0f, -180.167f),
	vec(606.75f, -484.833f),
	vec(590.583f, -476.166f),
	vec(575.917f, -465.833f),
	vec(560.25f, -456.5f),
	vec(452.5f, -309.0f),
	vec(455.5f, -326.0f),
	vec(460.0f, -342.5f),
	vec(465.0f, -359.5f),
	vec(471.5f, -374.5f),
	vec(480.0f, -389.0f),
	vec(491.0f, -402.0f),
	vec(502.364f, -416.364f),
	vec(514.636f, -426.545f),
	vec(528.818f, -438.909f),
	vec(543.364f, -447.455f),
	vec(-1532.5f, 320.25f),
	vec(-1515.5f, 323.5f),
	vec(-1500.5f, 325.75f),
	vec(-1430.17f, 331.937f),
	vec(-1411.17f, 331.187f),
	vec(-1393.92f, 331.187f),
	vec(-1375.79f, 330.937f),
	vec(-1357.04f, 330.687f),
	vec(-1086.25f, 471.875f),
	vec(-1484.0f, 324.75f),
	vec(-1467.0f, 329.5f),
	vec(-1448.5f, 328.75f),
	vec(-1640.5f, 462.125f),
	vec(-1621.63f, 467.25f),
	vec(-1600.63f, 470.0f),
	vec(-1583.38f, 470.0f),
	vec(-1565.25f, 469.75f),
	vec(-1546.5f, 471.5f),
	vec(-1529.5f, 472.25f),
	vec(-1511.0f, 471.5f),
	vec(-1439.17f, 475.687f),
	vec(-1420.17f, 474.937f),
	vec(-1402.92f, 474.937f),
	vec(-1384.79f, 474.687f),
	vec(-1366.04f, 477.437f),
	vec(-1349.04f, 478.187f),
	vec(-1330.54f, 479.437f),
	vec(-1309.04f, 479.937f),
	vec(-1290.79f, 479.437f),
	vec(-1271.23f, 479.988f),
	vec(-1252.5f, 479.375f),
	vec(-1233.75f, 479.125f),
	vec(-1216.75f, 479.875f),
	vec(-1123.0f, 479.125f),
	vec(-1103.63f, 478.75f),
	vec(-1056.63f, 444.0f),
	vec(-1025.88f, 398.0f),
	vec(-1072.25f, 458.25f),
	vec(-1045.0f, 429.5f),
	vec(-1034.5f, 414.25f),
	vec(-1493.0f, 472.5f),
	vec(-1476.0f, 473.25f),
	vec(-1457.5f, 475.5f),
	vec(-1585.0f, 313.667f),
	vec(-1566.0f, 316.667f),
	vec(-1548.0f, 317.167f),
	vec(-1022.5f, 382.0f),
	vec(-1018.0f, 365.5f),
	vec(-1015.0f, 348.0f),
	vec(-1012.0f, 330.0f),
	vec(-1010.0f, 312.0f),
	vec(-1007.5f, 293.0f),
	vec(-1007.5f, 273.5f),
	vec(-1003.5f, 255.0f),
	vec(-1002.0f, 238.0f),
	vec(-996.0f, 220.0f),
	vec(-997.5f, 206.0f),
	vec(-994.0f, 189.5f),
	vec(-986.5f, 172.5f),
	vec(-984.5f, 155.5f),
	vec(-977.0f, 139.0f),
	vec(-967.5f, 121.5f),
	vec(-956.5f, 105.0f),
	vec(-949.0f, 90.0f),
	vec(-937.5f, 76.0f),
	vec(-929.5f, 58.0f),
	vec(-920.0f, 43.5f),
	vec(-912.5f, 27.5f),
	vec(-903.0f, 12.5f),
	vec(-891.5f, -5.0f),
	vec(-880.0f, -21.0f),
	vec(-870.5f, -38.0f),
	vec(-861.5f, -53.5f),
	vec(-852.5f, -69.5f),
	vec(-840.0f, -85.0f),
	vec(-820.0f, -114.0f),
	vec(-810.5f, -128.0f),
	vec(-797.0f, -156.5f),
	vec(-789.5f, -172.5f),
	vec(-780.0f, -187.5f),
	vec(-768.5f, -205.0f),
	vec(-757.0f, -221.0f),
	vec(-747.5f, -238.0f),
	vec(-738.5f, -253.5f),
	vec(-729.5f, -269.5f),
	vec(-717.0f, -285.0f),
	vec(-827.667f, -99.6667f),
	vec(-653.159f, -347.875f),
	vec(-503.659f, -508.583f),
	vec(-519.659f, -512.083f),
	vec(-536.159f, -515.583f),
	vec(-552.159f, -520.083f),
	vec(-669.742f, -343.375f),
	vec(-682.659f, -330.292f),
	vec(-691.992f, -315.292f),
	vec(-706.326f, -299.625f),
	vec(-635.667f, -352.583f),
	vec(-603.083f, -355.417f),
	vec(-619.583f, -355.417f),
	vec(-566.75f, -353.75f),
	vec(-585.25f, -356.25f),
	vec(-418.75f, -467.5f),
	vec(-434.25f, -477.5f),
	vec(-452.75f, -487.5f),
	vec(-468.75f, -494.0f),
	vec(-485.25f, -501.5f),
	vec(-243.875f, -173.625f),
	vec(-227.875f, -163.375f),
	vec(-210.875f, -151.125f),
	vec(-195.625f, -141.375f),
	vec(-179.375f, -132.875f),
	vec(-162.875f, -123.875f),
	vec(-146.875f, -114.375f),
	vec(-132.875f, -103.625f),
	vec(-118.125f, -92.875f),
	vec(-102.125f, -82.625f),
	vec(-85.125f, -70.375f),
	vec(-69.875f, -60.625f),
	vec(-53.625f, -52.125f),
	vec(-402.396f, -460.938f),
	vec(-386.396f, -451.438f),
	vec(-372.396f, -440.688f),
	vec(-357.646f, -429.938f),
	vec(-341.646f, -419.688f),
	vec(-324.646f, -407.438f),
	vec(-309.396f, -397.688f),
	vec(-293.146f, -389.188f),
	vec(-277.271f, -379.563f),
	vec(-261.271f, -371.063f),
	vec(-247.271f, -360.313f),
	vec(-232.521f, -349.563f),
	vec(-216.521f, -339.313f),
	vec(-199.521f, -327.063f),
	vec(-184.271f, -317.313f),
	vec(-168.021f, -308.813f),
	vec(-153.521f, -301.813f),
	vec(-137.521f, -292.313f),
	vec(-123.521f, -281.563f),
	vec(-108.771f, -270.813f),
	vec(-92.7708f, -260.563f),
	vec(-75.7708f, -248.313f),
	vec(-60.5208f, -238.563f),
	vec(-44.2708f, -230.063f),
	vec(-25.7292f, -221.271f),
	vec(-9.7292f, -211.771f),
	vec(4.2708f, -201.021f),
	vec(21.0208f, -192.271f),
	vec(37.0208f, -182.021f),
	vec(54.0208f, -169.771f),
	vec(69.2708f, -160.021f),
	vec(85.521f, -151.521f),
	vec(101.396f, -141.896f),
	vec(117.396f, -132.396f),
	vec(131.396f, -121.646f),
	vec(146.146f, -110.896f),
	vec(162.146f, -100.646f),
	vec(177.146f, -90.3958f),
	vec(192.396f, -80.6458f),
	vec(208.646f, -72.1458f),
	vec(225.146f, -63.1458f),
	vec(241.146f, -53.6458f),
	vec(256.146f, -44.8958f),
	vec(270.896f, -34.1458f),
	vec(286.896f, -23.8958f),
	vec(303.896f, -11.6458f),
	vec(319.146f, -1.8958f),
	vec(335.396f, 6.6042f),
	vec(-36.0625f, -42.9375f),
	vec(-20.0625f, -33.4375f),
	vec(-6.0625f, -22.6875f),
	vec(8.6875f, -11.9375f),
	vec(24.6875f, -1.6875f),
	vec(41.6875f, 10.5625f),
	vec(56.9375f, 20.3125f),
	vec(73.1875f, 28.8125f),
	vec(89.062f, 38.4375f),
	vec(105.062f, 47.9375f),
	vec(119.062f, 58.6875f),
	vec(133.812f, 69.4375f),
	vec(149.812f, 79.6875f),
	vec(166.812f, 91.9375f),
	vec(183.062f, 103.688f),
	vec(199.312f, 112.188f),
	vec(215.812f, 121.188f),
	vec(231.812f, 130.688f),
	vec(245.812f, 141.438f),
	vec(260.562f, 152.188f),
	vec(276.562f, 162.438f),
	vec(293.562f, 174.688f),
	vec(308.812f, 184.438f),
	vec(325.062f, 192.938f),
	vec(342.271f, 201.729f),
	vec(358.271f, 209.229f),
	vec(372.271f, 217.979f),
	vec(387.021f, 228.729f),
	vec(403.021f, 238.979f),
	vec(420.021f, 251.229f),
	vec(435.271f, 260.979f),
	vec(454.521f, 267.479f),
	vec(470.396f, 274.104f),
	vec(486.396f, 281.604f),
	vec(502.396f, 288.354f),
	vec(518.146f, 297.104f),
	vec(531.146f, 305.354f),
	vec(548.146f, 317.604f),
	vec(563.396f, 322.354f),
	vec(579.646f, 330.854f),
	vec(596.146f, 336.854f),
	vec(612.146f, 343.354f),
	vec(627.146f, 351.104f),
	vec(640.896f, 359.854f),
	vec(659.146f, 366.854f),
	vec(678.896f, 374.354f),
	vec(695.396f, 378.354f),
	vec(714.396f, 380.521f),
	vec(355.375f, 10.4583f),
	vec(371.375f, 19.9583f),
	vec(387.375f, 32.7083f),
	vec(404.125f, 38.4583f),
	vec(421.125f, 46.7083f),
	vec(437.125f, 60.958f),
	vec(452.375f, 70.708f),
	vec(468.625f, 79.208f),
	vec(486.042f, 83.458f),
	vec(502.042f, 92.958f),
	vec(520.042f, 99.708f),
	vec(534.792f, 110.458f),
	vec(550.792f, 118.708f),
	vec(579.792f, 134.958f),
	vec(597.042f, 147.708f),
	vec(614.292f, 155.208f),
	vec(634.042f, 163.125f),
	vec(653.708f, 172.958f),
	vec(565.25f, 127.5f),
	vec(-2612.75f, -236.25f),
	vec(-2618.75f, -215.25f),
	vec(-2643.92f, -14.25f),
	vec(-2645.25f, 6.25f),
	vec(-2642.92f, 27.25f),
	vec(-2624.75f, -195.083f),
	vec(-2630.75f, -175.083f),
	vec(-2634.75f, -154.083f),
	vec(-2639.75f, -132.083f),
	vec(-2641.25f, -112.083f),
	vec(-2644.75f, -91.0833f),
	vec(-2644.75f, -71.0833f),
	vec(-2646.25f, -50.9166f),
	vec(-2645.58f, -31.5833f),
	vec(-1149.33f, -385.333f),
	vec(-1408.14f, -570.104f),
	vec(-1389.64f, -570.854f),
	vec(-1368.14f, -570.354f),
	vec(-1349.89f, -570.854f),
	vec(-1330.52f, -571.229f),
	vec(-1483.16f, 3.875f),
	vec(-1503.41f, 4.875f),
	vec(-1522.16f, 5.125f),
	vec(-1544.66f, 4.875f),
	vec(-1563.91f, 5.875f),
	vec(-1582.16f, 6.625f),
	vec(-1604.41f, 5.375f),
	vec(-1623.66f, 6.625f),
	vec(-1642.16f, 6.125f),
	vec(-1662.16f, 5.375f),
	vec(-1682.41f, 6.375f),
	vec(-1701.16f, 6.625f),
	vec(-1723.66f, 6.375f),
	vec(-1742.91f, 7.37497f),
	vec(-1761.16f, 8.12497f),
	vec(-1783.41f, 6.87497f),
	vec(-1800.31f, 6.0625f),
	vec(-1822.81f, 5.8125f),
	vec(-1842.06f, 6.81247f),
	vec(-1857.04f, 7.64583f),
	vec(-1875.17f, 6.52083f),
	vec(-1893.67f, 6.02083f),
	vec(-1911.8f, 5.0f),
	vec(-1932.8f, 6.25f),
	vec(-1955.3f, 6.0f),
	vec(-1975.3f, 6.5f),
	vec(-1996.3f, 7.75f),
	vec(-2018.8f, 7.5f),
	vec(-2038.05f, 8.5f),
	vec(-1949.55f, 80.9845f),
	vec(-1932.8f, 90.0155f),
	vec(-1802.55f, 193.683f),
	vec(-1914.63f, 100.266f),
	vec(-1900.63f, 114.078f),
	vec(-1884.88f, 124.578f),
	vec(-1870.63f, 135.453f),
	vec(-1855.38f, 146.453f),
	vec(-1841.13f, 156.37f),
	vec(-1337.27f, 328.219f),
	vec(-1318.77f, 327.469f),
	vec(-1297.27f, 327.969f),
	vec(-1279.02f, 327.469f),
	vec(-1259.46f, 328.019f),
	vec(-1240.73f, 327.406f),
	vec(-1221.98f, 327.156f),
	vec(-1204.98f, 324.906f),
	vec(-1191.23f, 311.781f),
	vec(-1178.73f, 298.281f),
	vec(-1166.23f, 282.281f),
	vec(-1158.23f, 265.281f),
	vec(-1155.73f, 246.781f),
	vec(-1155.73f, 227.281f),
	vec(-1153.73f, 207.281f),
	vec(-1152.73f, 190.281f),
	vec(-1150.23f, 172.781f),
	vec(-1151.23f, 152.281f),
	vec(-1148.73f, 137.781f),
	vec(-1142.0f, 119.75f),
	vec(-1136.5f, 101.75f),
	vec(-1132.5f, 84.75f),
	vec(-1125.5f, 67.25f),
	vec(-1119.0f, 49.75f),
	vec(-1114.0f, 32.25f),
	vec(-1104.0f, 14.0f),
	vec(-1093.5f, -2.0f),
	vec(-1082.5f, -19.5f),
	vec(-1071.0f, -37.0f),
	vec(-1060.0f, -52.0f),
	vec(-1053.75f, -69.25f),
	vec(-1043.75f, -84.75f),
	vec(-1032.25f, -100.75f),
	vec(-1021.25f, -113.25f),
	vec(-1011.75f, -126.75f),
	vec(-1003.75f, -142.25f),
	vec(-995.25f, -158.25f),
	vec(-985.25f, -173.25f),
	vec(-972.75f, -189.25f),
	vec(-960.25f, -204.75f),
	vec(-951.75f, -221.0f),
	vec(-940.25f, -238.5f),
	vec(-929.25f, -253.5f),
	vec(-918.25f, -270.0f),
	vec(-908.25f, -285.5f),
	vec(-896.75f, -301.5f),
	vec(-885.75f, -314.0f),
	vec(-876.25f, -327.5f),
	vec(-868.25f, -343.0f),
	vec(-805.25f, -142.0f),
	vec(-859.75f, -359.0f),
	vec(-849.75f, -374.0f),
	vec(-837.25f, -390.0f),
	vec(-727.617f, -496.629f),
	vec(-824.383f, -407.371f),
	vec(-744.503f, -487.583f),
	vec(-813.208f, -424.17f),
	vec(-802.875f, -440.503f),
	vec(-788.875f, -451.837f),
	vec(-775.208f, -465.837f),
	vec(-760.208f, -476.17f),
	vec(-571.292f, -522.0f),
	vec(-590.542f, -521.792f),
	vec(-609.042f, -524.792f),
	vec(-628.542f, -526.292f),
	vec(-647.042f, -526.792f),
	vec(-665.042f, -524.042f),
	vec(-681.875f, -518.208f),
	vec(-698.042f, -512.541f),
	vec(-712.708f, -502.208f),
	vec(-430.688f, -295.563f),
	vec(-446.188f, -306.563f),
	vec(-414.938f, -285.063f),
	vec(-398.938f, -275.563f),
	vec(-384.938f, -264.813f),
	vec(-370.188f, -254.063f),
	vec(-354.188f, -243.813f),
	vec(-337.188f, -231.563f),
	vec(-321.938f, -221.813f),
	vec(-305.688f, -213.313f),
	vec(-289.813f, -203.688f),
	vec(-273.813f, -194.188f),
	vec(-259.813f, -183.438f),
	vec(-462.75f, -318.0f),
	vec(-478.75f, -325.5f),
	vec(-495.25f, -333.0f),
	vec(-511.25f, -337.5f),
	vec(-529.75f, -344.5f),
	vec(-549.25f, -350.0f),
	vec(-1197.25f, 481.5f),
	vec(-1144.25f, 478.5f),
	vec(-1179.25f, 478.5f),
	vec(-1161.75f, 477.5f),
	vec(441.0f, -252.0f),
	vec(573.333f, -39.6667f),
	vec(843.364f, 405.455f),
	vec(1346.5f, 533.5f),
	vec(1347.0f, 515.5f),
	vec(1347.5f, 500.5f),
	vec(1349.0f, 481.0f),
	vec(1349.0f, 461.0f),
	vec(1348.5f, 444.5f),
	vec(1351.5f, 425.0f),
	vec(1352.0f, 403.5f),
	vec(1353.5f, 382.5f),
	vec(1356.25f, 363.25f),
	vec(1358.25f, 343.25f),
	vec(1360.25f, 324.25f),
	vec(1359.75f, 303.25f),
	vec(1359.75f, 288.25f),
	vec(1360.75f, 268.25f),
	vec(1360.75f, 247.75f),
	vec(1365.25f, 228.75f),
	vec(1365.25f, 213.75f),
	vec(1366.25f, 193.75f),
	vec(1368.25f, 153.917f),
	vec(1088.45f, 141.909f),
	vec(1089.64f, 124.0f),
	vec(1293.33f, -267.917f),
	vec(1288.83f, -289.417f),
	vec(1280.83f, -306.917f),
	vec(1265.17f, -323.25f),
	vec(1148.33f, -363.437f),
	vec(1133.33f, -367.937f),
	vec(1364.13f, 172.917f),
	vec(1276.63f, -1.75f),
	vec(1277.88f, -22.25f),
	vec(1279.38f, -42.25f),
	vec(1280.38f, -64.25f),
	vec(1282.88f, -84.25f),
	vec(1287.13f, -103.75f),
	vec(1287.63f, -123.75f),
	vec(1288.88f, -144.25f),
	vec(1290.38f, -164.25f),
	vec(1291.38f, -186.25f),
	vec(1293.88f, -206.25f),
	vec(1291.88f, -226.25f),
	vec(1276.04f, 59.5834f),
	vec(1276.54f, 39.5834f),
	vec(1277.79f, 19.0834f),
	vec(1292.0f, -246.667f),
	vec(690.0f, -506.0f),
	vec(639.455f, -501.273f),
	vec(1088.33f, 771.333f),
	vec(1181.46f, -350.74f),
	vec(1163.96f, -357.615f),
	vec(1248.71f, -327.052f),
	vec(1231.21f, -333.927f),
	vec(1214.71f, -341.427f),
	vec(1198.71f, -345.927f),
	vec(818.5f, -70.5f),
	vec(-2209.33f, 459.333f),
};

const vec TiledEntities::spawn = vec(326.5f, 653.5f);

const std::array<vec, 28> TiledEntities::enemy_spawn = {
	vec(843.0f, 656.0f),
	vec(844.0f, 721.0f),
	vec(-672.0f, 705.0f),
	vec(-1314.0f, 707.0f),
	vec(-1954.0f, 708.0f),
	vec(-2077.0f, 597.0f),
	vec(-2156.0f, 400.0f),
	vec(-2464.0f, 204.0f),
	vec(-2548.0f, -174.0f),
	vec(-2264.0f, -478.0f),
	vec(-1826.0f, -509.0f),
	vec(-1309.0f, -481.0f),
	vec(-2002.0f, -58.0f),
	vec(-1942.0f, -60.0f),
	vec(-1902.0f, -60.0f),
	vec(-978.0f, -36.0f),
	vec(-792.0f, -302.0f),
	vec(-230.0f, -260.0f),
	vec(-202.0f, -234.0f),
	vec(40.0f, -84.0f),
	vec(72.0f, -60.0f),
	vec(344.0f, 94.0f),
	vec(380.0f, 124.0f),
	vec(734.0f, 316.0f),
	vec(1196.0f, 136.0f),
	vec(-1824.0f, -486.0f),
	vec(-932.0f, -106.0f),
	vec(-870.0f, -200.0f),
};



const std::array<vec, 40> TiledPolygons::outter = {
	vec(-1330.0f,-588.0f),
	vec(-2170.0f,-576.0f),
	vec(-2400.67f,-489.3333f),
	vec(-2540.67f,-382.66700000000003f),
	vec(-2619.33f,-205.33300000000003f),
	vec(-2639.33f,10.66700000000003f),
	vec(-2600.67f,158.66700000000003f),
	vec(-2466.0f,318.66700000000003f),
	vec(-2195.333f,449.3299999999999f),
	vec(-2140.667f,656.0f),
	vec(-2087.333f,738.6700000000001f),
	vec(-1962.0f,784.0f),
	vec(1055.33f,770.6700000000001f),
	vec(1230.0f,702.6700000000001f),
	vec(1339.33f,578.6700000000001f),
	vec(1372.67f,136.0f),
	vec(1280.67f,76.0f),
	vec(1306.0f,-280.0f),
	vec(1270.0f,-334.66700000000003f),
	vec(668.6700000000001f,-522.6667f),
	vec(542.0f,-452.0f),
	vec(468.6700000000001f,-374.66700000000003f),
	vec(444.6700000000001f,-250.66699999999997f),
	vec(478.0f,-104.0f),
	vec(659.3299999999999f,-4.0f),
	vec(788.6700000000001f,229.33299999999997f),
	vec(-479.33299999999997f,-520.0f),
	vec(-612.667f,-538.6667f),
	vec(-706.0f,-520.0f),
	vec(-779.333f,-473.33299999999997f),
	vec(-1131.333f,72.0f),
	vec(-1144.667f,244.0f),
	vec(-1191.333f,317.33299999999997f),
	vec(-1568.667f,312.0f),
	vec(-2027.333f,-1.33299999999997f),
	vec(-1388.6667f,-6.66700000000003f),
	vec(-1230.0f,-105.33300000000003f),
	vec(-1142.0f,-294.667f),
	vec(-1144.667f,-434.66700000000003f),
	vec(-1230.0f,-554.6667f),
};
const std::array<vec, 41> TiledPolygons::inner = {
	vec(-1376.0f,-442.0f),
	vec(-1300.0f,-360.0f),
	vec(-1304.0f,-268.0f),
	vec(-1396.0f,-162.0f),
	vec(-1466.0f,-132.0f),
	vec(-2126.0f,-128.0f),
	vec(-2194.0f,-56.0f),
	vec(-2206.0f,48.0f),
	vec(-2134.0f,142.0f),
	vec(-1624.0f,462.0f),
	vec(-1072.0f,466.0f),
	vec(-1014.0f,384.0f),
	vec(-980.0f,134.0f),
	vec(-668.0f,-354.0f),
	vec(-564.0f,-370.0f),
	vec(-464.0f,-332.0f),
	vec(686.0f,368.0f),
	vec(862.0f,400.0f),
	vec(968.0f,368.0f),
	vec(1002.0f,300.0f),
	vec(868.0f,-74.0f),
	vec(654.0f,-164.0f),
	vec(622.0f,-272.0f),
	vec(648.0f,-326.0f),
	vec(748.0f,-376.0f),
	vec(1116.0f,-226.0f),
	vec(1088.0f,158.0f),
	vec(1196.0f,220.0f),
	vec(1186.0f,478.0f),
	vec(1062.0f,582.0f),
	vec(934.0f,610.0f),
	vec(-1968.0f,608.0f),
	vec(-2020.0f,516.0f),
	vec(-2028.0f,380.0f),
	vec(-2070.0f,296.0f),
	vec(-2368.0f,150.0f),
	vec(-2454.0f,46.0f),
	vec(-2472.0f,-96.0f),
	vec(-2428.0f,-244.0f),
	vec(-2264.0f,-382.0f),
	vec(-2082.0f,-444.0f),
};



