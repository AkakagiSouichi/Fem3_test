// fem3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <iomanip>

class obj {
    int id;
    int no_use[6];
    double D[3][3];
    double B[3][6];
    double BT[6][3];
    double node_xy[2][6];
    double node_x[6];
    double node_y[6];
    double temp[6][3];
    public:double K[6][6];
          double gousei[12][12];

          void set_id(int i) {
              this->id = i;
              d_matrix();
          }

          int get_id() {
              return this->id;
          }

          void d_matrix(void) {
              D[0][0] = 1;      D[0][1] = 0.5;  D[0][2] = 0;
              D[1][0] = 0.5;    D[1][1] = 1;    D[1][2] = 0;
              D[2][0] = 0;      D[2][1] = 0;    D[2][2] = 1;
              Node_xy();
          }

          void Node_xy(void) {
              node_xy[0][0] = 0;    node_xy[0][1] = 1;  node_xy[0][2] = 2;  node_xy[0][3] = 2;  node_xy[0][4] = 1;  node_xy[0][5] = 0;
              node_xy[1][0] = 0;    node_xy[1][1] = 0;  node_xy[1][2] = 0;  node_xy[1][3] = 1;  node_xy[1][4] = 1;  node_xy[1][5] = 1;
              Node();
          }

          void Node(void) {
              if (get_id() == 1 || get_id() == 2) {
                  node_x[0] = node_xy[0][0];   node_x[1] = node_xy[0][1];   node_x[2] = node_xy[0][4];
                  node_y[0] = node_xy[1][0];   node_y[1] = node_xy[1][1];   node_y[2] = node_xy[1][4];
              }
              else if (get_id() == 3 || get_id() == 4) {
                  node_x[0] = node_xy[0][1];   node_x[1] = node_xy[0][3];   node_x[2] = node_xy[0][4];
                  node_y[0] = node_xy[1][1];   node_y[1] = node_xy[1][3];   node_y[2] = node_xy[1][4];
              }
  
              b_matrix();
          }

          void b_matrix(void) {
              B[0][0] = node_y[1] - node_y[2];      B[0][1] = 0;                        B[0][2] = node_y[2] - node_y[0];    B[0][3] = 0;                            B[0][4] = node_y[0] - node_y[1];    B[0][5] = 0;
              B[1][0] = 0;                          B[1][1] = node_x[2] - node_x[1];    B[1][2] = 0;                        B[1][3] = node_x[0] - node_x[2];        B[1][4] = 0;                        B[1][5] = node_x[1] - node_x[0];
              B[2][0] = node_x[2] - node_x[1];      B[2][1] = node_y[1] - node_y[2];    B[2][2] = node_x[0] - node_x[2];    B[2][3] = node_y[2] - node_y[0];        B[2][4] = node_x[1] - node_x[0];    B[2][5] = node_y[0] - node_y[1];

              inv_b_matrix();
          }

          void inv_b_matrix(void) {
              for (int i = 0; i < 3; i++) {
                  for (int j = 0; j < 6; j++) {
                      BT[j][i] = B[i][j];
                  }
              }
              Temp();
          }

          void Temp(void) {
              for (int i = 0; i < 6; i++) {
                  for (int j = 0; j < 3; j++) {
                      temp[i][j] = 0;
                      for (int k = 0; k < 3; k++) {
                          temp[i][j] += BT[i][k] * D[k][j];
                      }
                  }
              }
              k_matrix();
          }

          void k_matrix(void) {
              for (int i = 0; i < 6; i++) {
                  for (int j = 0; j < 6; j++) {
                      K[i][j] = 0;
                      for (int k = 0; k < 3; k++) {
                          K[i][j] += temp[i][k] * B[k][j];
                      }
                  }
              }
              no_use_node();
          }

          void no_use_node(void) {
              switch (get_id())
              {
              case 1:
                  no_use[0] = 4;
                  no_use[1] = 5;
                  no_use[2] = 6;
                  no_use[3] = 7;
                  no_use[4] = 10;
                  no_use[5] = 11;
                  Gousei();
                  break;

              case 2:
                  no_use[0] = 0;
                  no_use[1] = 1;
                  no_use[2] = 8;
                  no_use[3] = 9;
                  no_use[4] = 10;
                  no_use[5] = 11;
                  Gousei();
                  break;

              case 3:
                  no_use[0] = 0;
                  no_use[1] = 1;
                  no_use[2] = 4;
                  no_use[3] = 5;
                  no_use[4] = 10;
                  no_use[5] = 11;
                  Gousei();
                  break;

              case 4:
                  no_use[0] = 2;
                  no_use[1] = 3;
                  no_use[2] = 4;
                  no_use[3] = 5;
                  no_use[4] = 6;
                  no_use[5] = 7;
                  Gousei();
                  break;

              default:
                  break;
              }
          }

          void Gousei(void) {
              int i;
              int stack1 = 0;
              int stack2 = 0;
              for (i = 0; i < 12; i++) {
                  if (i == no_use[0] || i == no_use[1] || i == no_use[2] || i == no_use[3] || i == no_use[4] || i == no_use[5]) {
                      stack1++;
                  }
                  for (int j = 0; j < 12; j++) {
                      if (i == no_use[0] || i == no_use[1] || i == no_use[2] || i == no_use[3] || i == no_use[4] || i == no_use[5]) {
                          gousei[i][j] = 0;
                      }
                      else if (j == no_use[0] || j == no_use[1] || j == no_use[2] || j == no_use[3] || j == no_use[4] || j == no_use[5]) {
                          stack2++;
                          gousei[i][j] = 0;
                      }
                      else {
                          gousei[i][j] = K[i-stack1][j-stack2];
                      }
                  }
                  stack2 = 0;
              }
          }

          void show(void) {
              for (int i = 0; i < 12; i++) {
                  for (int j = 0; j < 12; j++) {
                      std::cout << gousei[i][j] << "\t" << std::ends;
                  }
                  std::cout << "\n" << std::endl;
              }
          }

};


double Ka[12][12];
double Kb[8][8];
double inv_Kb[8][8];
double f[8][1] = { 0, 0, 0, 0, 0, 1, 0, 0, };
double u[8][1];

double buf;
int i, j, k;
int n = 8;

int main()
{
    obj* onj1 = new obj();
    onj1->set_id(1);
    
    obj* onj2 = new obj();
    onj2->set_id(2);
    
    obj* onj3 = new obj();
    onj3->set_id(3);

    obj* onj4 = new obj();
    onj4->set_id(4);

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            Ka[i][j] = onj1->gousei[i][j] + onj2->gousei[i][j] + onj3->gousei[i][j] + onj4->gousei[i][j];
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Kb[i][j] = Ka[i + 2][j + 2];
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inv_Kb[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (i = 0; i < n; i++) {
        buf = 1 / Kb[i][i];
        for (j = 0; j < n; j++) {
            Kb[i][j] *= buf;
            inv_Kb[i][j] *= buf;
        }
        for (j = 0; j < n; j++) {
            if (i != j) {
                buf = Kb[j][i];
                for (k = 0; k < n; k++) {
                    Kb[j][k] -= Kb[i][k] * buf;
                    inv_Kb[j][k] -= inv_Kb[i][k] * buf;
                }
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 1; j++) {
            u[i][j] = 0;
            for (int k = 0; k < 8; k++) {
                u[i][j] += inv_Kb[i][k] * f[k][j];
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 1; j++) {
            std::cout << std::fixed << std::setprecision(2) <<u[i][j] << "\t" << std::ends;
        }
        std::cout << "\n" << std::endl;
    }
}