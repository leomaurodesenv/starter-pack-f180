//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    main.cpp
  \brief   The ssl-vision application entry point.
  \author  Stefan Zickler, (C) 2008
*/
//========================================================================

//#include <QApplication>
//#include <QCleanlooksStyle>
//#include <QPlastiqueStyle>
//#include "mainwindow.h"

#include <stdio.h>
#include <QThread>
#include <QtNetwork>
#include <math.h>
#include "robocup_ssl_client.h"
#include "timer.h"

#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

#include "grSim_Packet.pb.h"
#define VELOCIDADEMAXIMA 30

void printRobotInfo(const SSL_DetectionRobot & robot) {
    printf("CONF=%4.2f ", robot.confidence());
    if (robot.has_robot_id()) {
        printf("ID=%3d ",robot.robot_id());
    } else {
        printf("ID=N/A ");
    }
    printf(" HEIGHT=%6.2f POS=<%9.2f,%9.2f> ",robot.height(),robot.x(),robot.y());
    if (robot.has_orientation()) {
        printf("ANGLE=%6.3f ",robot.orientation());
    } else {
        printf("ANGLE=N/A    ");
    }
    printf("RAW=<%8.2f,%8.2f>\n",robot.pixel_x(),robot.pixel_y());
}


void command(bool yellow, int id, double wheel1, double wheel2, double wheel3, double wheel4, double kickspeedx, double kickspeedz){
/** Códigos do mainwindow.cpp do GrSim **/
    grSim_Packet packetGRSim;

    packetGRSim.mutable_commands()->set_isteamyellow(yellow);
    packetGRSim.mutable_commands()->set_timestamp(0.0);
    grSim_Robot_Command* command = packetGRSim.mutable_commands()->add_robot_commands();
    command->set_id(id);

    command->set_wheelsspeed(true);
    command->set_wheel1(wheel1);
    command->set_wheel2(wheel2);
    command->set_wheel3(wheel3);
    command->set_wheel4(wheel4);
    command->set_veltangent(0);
    command->set_velnormal(0);
    command->set_velangular(0);

    command->set_kickspeedx(kickspeedx);
    command->set_kickspeedz(kickspeedz);
    command->set_spinner(false);
    QByteArray dgram;
    dgram.resize(packetGRSim.ByteSize());
    packetGRSim.SerializeToArray(dgram.data(), dgram.size());
    QString _port = "20011";
    QHostAddress* _addr = new QHostAddress("127.0.0.1");
    QUdpSocket udpsocket;

    quint16 _port2 = _port.toUShort();	
    udpsocket.writeDatagram(dgram, *_addr, _port2);
    /** Fim **/


}

void MoverPara(double x, double y, float rRotation, double rX, double rY)
{
	// Declara variáveis.
	float k, Theta, Angulo, Dist, vr, vl, ModTheta;
	// Calcula a distância entre o robo e o ponto desejado.
	Dist = sqrt( (x-rX)*(x-rX) + (y-rY)*(y-rY) );

	// Calcula quantos graus o robô deve girar para
	// ficar em direção ao ponto desejado.
	Angulo = (180/M_PI)*atan2(y-rY, x-rX);
	Theta = Angulo - rRotation*(180/M_PI);
	printf("Dist %.3f rRotation %.3f ang %.3f theta %.3f\n",Dist,rRotation,Angulo,Theta);

	// Ajusta o ângulo.
	while (Theta > 180) Theta -= 360;
	while (Theta < -180) Theta += 360;
	// ModTheta = |theta|.
	ModTheta = fabs(Theta);
	
//	Determina a velocidade de rotação
// de acordo com o módulo do ângulo
// que o robô precisa girar.
// OBS: Esses valores podem ser alterados para
// alterar a velocidade de rotação
// do robô enquanto ele vai de encontro ao ponto (x,y).
if( ModTheta > 100)
{
k = 0.50*VELOCIDADEMAXIMA;
}else if (ModTheta > 90)
{
k = 0.35*VELOCIDADEMAXIMA;
}else if (ModTheta > 50)
{
 k = 0.20*VELOCIDADEMAXIMA;
}else if (ModTheta > 20)
{
k = 0.15*VELOCIDADEMAXIMA;
}else if (ModTheta >= 1)
{
k = 0.1*VELOCIDADEMAXIMA;
}else
{
k = 0;
}
// Define o valor da velocidade para a roda esquerda e direita.
// A velocidade diminui conforme o jogador se aproxima do alvo e
// a rotação do robô diminui conforme o ângulodiminui.
if(Theta > 0)
{
vl = VELOCIDADEMAXIMA*(1.0 - exp(-Dist/20));
vr = (VELOCIDADEMAXIMA - 2*k)*(1.0 - exp(-Dist/20));
}else
{
vl = (VELOCIDADEMAXIMA - 2*k)*(1.0 - exp(-Dist/20));
vr = VELOCIDADEMAXIMA*(1.0 - exp(-Dist/20));
} 


	printf("dist %.3f k %.3f Theta %.3f vl %.3f vr %.3f \n",Dist, k, ModTheta,vl,vr);
	command(true,2,-vr,-vr,vl,vl,0,0);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    RoboCupSSLClient client;
    client.open(true);
    SSL_WrapperPacket packet;

    
    while(true) {
        if (client.receive(packet)) {
            printf("-----Received Wrapper Packet---------------------------------------------\n");
            //see if the packet contains a robot detection frame:
            if (packet.has_detection()) {
                SSL_DetectionFrame detection = packet.detection();
                //Display the contents of the robot detection results:
                double t_now = GetTimeSec();

                printf("-[Detection Data]-------\n");
                //Frame info:
                printf("Camera ID=%d FRAME=%d T_CAPTURE=%.4f\n",detection.camera_id(),detection.frame_number(),detection.t_capture());

                printf("SSL-Vision Processing Latency                   %7.3fms\n",(detection.t_sent()-detection.t_capture())*1000.0);
                printf("Network Latency (assuming synched system clock) %7.3fms\n",(t_now-detection.t_sent())*1000.0);
                printf("Total Latency   (assuming synched system clock) %7.3fms\n",(t_now-detection.t_capture())*1000.0);
                int balls_n = detection.balls_size();
                int robots_blue_n =  detection.robots_blue_size();
                int robots_yellow_n =  detection.robots_yellow_size();

                //Ball info:
                for (int i = 0; i < balls_n; i++) {
                    SSL_DetectionBall ball = detection.balls(i);
                    printf("-Ball (%2d/%2d): CONF=%4.2f POS=<%9.2f,%9.2f> ", i+1, balls_n, ball.confidence(),ball.x(),ball.y());
                    if (ball.has_z()) {
                        printf("Z=%7.2f ",ball.z());
                    } else {
                        printf("Z=N/A   ");
                    }
                    printf("RAW=<%8.2f,%8.2f>\n",ball.pixel_x(),ball.pixel_y());
                }

                //Blue robot info:
                for (int i = 0; i < robots_blue_n; i++) {
                    SSL_DetectionRobot robot = detection.robots_blue(i);
                    printf("-Robot(B) (%2d/%2d): ",i+1, robots_blue_n);
                    printRobotInfo(robot);
		    //robot.x(), robot.y(), robot.orientation()
		    //ball.pixel_x(),ball.pixel_y()
                }

                //Yellow robot info:
                for (int i = 0; i < robots_yellow_n; i++) {
                    SSL_DetectionRobot robot = detection.robots_yellow(i);
                    printf("-Robot(Y) (%2d/%2d): ",i+1, robots_yellow_n);
                    printRobotInfo(robot);
	 	    if(i==2){		
MoverPara(detection.balls(0).pixel_x(),detection.balls(0).pixel_y(),robot.orientation(),robot.pixel_x(),robot.pixel_y());
		    }
                }

            }

            //see if packet contains geometry data:
            if (packet.has_geometry()) {
                const SSL_GeometryData & geom = packet.geometry();
                printf("-[Geometry Data]-------\n");

                const SSL_GeometryFieldSize & field = geom.field();
                printf("Field Dimensions:\n");
                printf("  -line_width=%d (mm)\n",field.line_width());
                printf("  -field_length=%d (mm)\n",field.field_length());
                printf("  -field_width=%d (mm)\n",field.field_width());
                printf("  -boundary_width=%d (mm)\n",field.boundary_width());
                printf("  -referee_width=%d (mm)\n",field.referee_width());
                printf("  -goal_width=%d (mm)\n",field.goal_width());
                printf("  -goal_depth=%d (mm)\n",field.goal_depth());
                printf("  -goal_wall_width=%d (mm)\n",field.goal_wall_width());
                printf("  -center_circle_radius=%d (mm)\n",field.center_circle_radius());
                printf("  -defense_radius=%d (mm)\n",field.defense_radius());
                printf("  -defense_stretch=%d (mm)\n",field.defense_stretch());
                printf("  -free_kick_from_defense_dist=%d (mm)\n",field.free_kick_from_defense_dist());
                printf("  -penalty_spot_from_field_line_dist=%d (mm)\n",field.penalty_spot_from_field_line_dist());
                printf("  -penalty_line_from_spot_dist=%d (mm)\n",field.penalty_line_from_spot_dist());

                int calib_n = geom.calib_size();
                for (int i=0; i< calib_n; i++) {
                    const SSL_GeometryCameraCalibration & calib = geom.calib(i);
                    printf("Camera Geometry for Camera ID %d:\n", calib.camera_id());
                    printf("  -focal_length=%.2f\n",calib.focal_length());
                    printf("  -principal_point_x=%.2f\n",calib.principal_point_x());
                    printf("  -principal_point_y=%.2f\n",calib.principal_point_y());
                    printf("  -distortion=%.2f\n",calib.distortion());
                    printf("  -q0=%.2f\n",calib.q0());
                    printf("  -q1=%.2f\n",calib.q1());
                    printf("  -q2=%.2f\n",calib.q2());
                    printf("  -q3=%.2f\n",calib.q3());
                    printf("  -tx=%.2f\n",calib.tx());
                    printf("  -ty=%.2f\n",calib.ty());
                    printf("  -tz=%.2f\n",calib.tz());

                    if (calib.has_derived_camera_world_tx() && calib.has_derived_camera_world_ty() && calib.has_derived_camera_world_tz()) {
                      printf("  -derived_camera_world_tx=%.f\n",calib.derived_camera_world_tx());
                      printf("  -derived_camera_world_ty=%.f\n",calib.derived_camera_world_ty());
                      printf("  -derived_camera_world_tz=%.f\n",calib.derived_camera_world_tz());
                    }

                }
            }
        }
    }

    return 0;
}
