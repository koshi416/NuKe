// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright Drew Noakes 2013-2016

#include "joystick.hpp"
#include <cmath>
#include <iostream>
#include <unistd.h>

char *type = "";
double Lx, Ly, Rx, Ry;
double Lrad, Rrad;
double p1, p2, p3, p4;
double r2d2 = sqrt(2) / 3.0;
double vx, vy;
int main() {
  // Create an instance of Joystick
  Joystick joystick("/dev/input/js0");

  // Ensure that it was found and that we can use it
  if (!joystick.isFound()) {
    printf("open failed.\n");
    exit(1);
  }

  while (true) {
    // Restrict rate
    usleep(1000);

    // Attempt to sample an event from the joystick
    JoystickEvent event;
    if (joystick.sample(&event)) {
      if (event.isButton()) {
        switch (event.number) {
        case 0:
          type = "SELECT";
          break;
        case 1:
          type = "LStick";
          break;
        case 2:
          type = "RStick";
          break;
        case 3:
          type = "START";
          break;
        case 4:
          type = "↑";
          break;
        case 5:
          type = "→";
          break;
        case 6:
          type = "↓";
          break;
        case 7:
          type = "←";
          break;
        case 8:
          type = "L2";
          break;
        case 9:
          type = "R2";
          break;
        case 10:
          type = "L1";
          break;
        case 11:
          type = "R1";
          break;
        case 12:
          type = "△";
          break;
        case 13:
          type = "○";
          break;
        case 14:
          type = "☓";
          break;
        case 15:
          type = "□";
          break;
        case 16:
          type = "PS3Mark";
          break;
        }
        printf("Button %s is %s\n", type, event.value == 0 ? "up" : "down");
      } else if (event.isAxis()) {
        if (event.number < 4) {
          switch (event.number) {
          case 0:
            Lx = event.value / 32767.0;
            break;
          case 1:
            Ly = -event.value / 32767.0;
            break;
          case 2:
            Rx = event.value / 32767.0;
            break;
          case 3:
            Ry = -event.value / 32767.0;
            break;
          }
          Lrad = std::atan2(Ly, Lx) * 180.0 / M_PI;
          Rrad = std::atan2(Ry, Rx) * 180.0 / M_PI;
          p1 = r2d2 * (Ry - Rx);
          p2 = -r2d2 * (Ry + Rx);
          p3 = r2d2 * (Rx - Ry);
          p4 = r2d2 * (Rx + Ry);
          printf("p1:%lf,p2:%lf,p3:%lf,p4:%lf,deg:%lf\n", p1, p2, p3, p4, Rrad);
          // printf("L(x,y,rad)=(%lf,%lf,%lf),R(x,y,rad)=(%lf,%lf,%lf)\n", Lx,
          // Ly,Lrad, Rx, Ry, Rrad);
        }
      }
    }
  }
}
