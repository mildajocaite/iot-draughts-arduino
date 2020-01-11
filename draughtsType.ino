const long white [] = {6535894, 6537971, 2147809, 6535827,
                       2156465, 6538566, 6534856, 2086548,
                       2068404, 6538615, 6534036, 6530835
                      };
const long black [] = {2077657, 2080195, 2106558, 1821658,
                       2139138, 2111841, 6538463, 1847810,
                       6535645, 2109359, 6534174, 1821731
                      };
const long whiteKing [] = {1802676, 1844452, 1830400, 1818934,
                           1856500, 1819088, 1865198, 6534109,
                           1803571, 6533122, 1820071, 1824118
                          };
const long blackKing [] = {1819217, 1822644, 1831200, 1812789,
                           1823642, 1858086, 1858057, 1865483,
                           1820068, 1850397, 1860255, 1844420
                          };

long returnDraughtType(long tag) {
  Serial.println(tag);
  for (int j = 0; j < 12; j++) {
    if (white[j] == tag) {
      return 1;
    }
  }
  for (int i = 0; i < 12; i++) {
    if (black[i] == tag) {
      return 2;
    }
  }
  for (int i = 0; i < 12; i++) {
    if (whiteKing[i] == tag) {
      return 3;
    }
  }
  for (int i = 0; i < 12; i++) {
    if (blackKing[i] == tag) {
      return 4;
    }
  }
  return 5;
}
