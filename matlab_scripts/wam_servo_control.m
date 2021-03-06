function wam_servo_control(  )
%wam_servo_control Control WAM arm using servos.
sim = GazeboMatlabSimulator;
sim.Reset;
tf = 5;
h = 0.1;%Step for only visualization as servo control is happening at 1Khz in plugin
N = round(tf/h);%Number of steps to run
sim.AttachServo(1:5,[300.0;20.0;300.0],[10;-10;500;-500]); %Attach servos for joint angle control
sim.AttachServo(6:7,[100.0;20.0;100.0],[10;-10;30;-30]);
sim.AttachServo(8:15,[5.0;1.0;10.0],[10;-10;30;-30]);
sim.ActuatedJoints = 1:15;
us = [-1;-1;1;-0.5;1;-1;1;0.5;0.5;1;1;1;0;0;0];%Desired Joint Angles
%Visualization:
m = MarkerInfo;
sim.PublishTrajectory([1.2462; 0; 0.7810],m);%Initialposition from foward kin
m.action = m.ADD;
uall = zeros(15,N);
for i = 1:N
    [LinkData,JointData] = sim.Step(h,us);%Run simulation. Servo control is happening with desired joint angles as us
    sim.PublishTrajectory(LinkData{1}.position,m);%Publish the current end effector position.
    uall(:,i) = JointData(1,:)';
end
figure; 
subplot(4,2,1), plot((1:N)*h,uall(1,:)), hold on, plot((1:N)*h,us(1)*ones(1,N),'r'),xlabel('t'), ylabel('u1');
subplot(4,2,2), plot((1:N)*h,uall(2,:)), hold on, plot((1:N)*h,us(2)*ones(1,N),'r'),xlabel('t'), ylabel('u2');
subplot(4,2,3), plot((1:N)*h,uall(3,:)), hold on, plot((1:N)*h,us(3)*ones(1,N),'r'),xlabel('t'), ylabel('u3');
subplot(4,2,4), plot((1:N)*h,uall(4,:)), hold on, plot((1:N)*h,us(4)*ones(1,N),'r'),xlabel('t'), ylabel('u4');
subplot(4,2,5), plot((1:N)*h,uall(5,:)), hold on, plot((1:N)*h,us(5)*ones(1,N),'r'),xlabel('t'), ylabel('u5');
subplot(4,2,6), plot((1:N)*h,uall(6,:)), hold on, plot((1:N)*h,us(6)*ones(1,N),'r'),xlabel('t'), ylabel('u6');
subplot(4,2,7), plot((1:N)*h,uall(7,:)), hold on, plot((1:N)*h,us(7)*ones(1,N),'r'),xlabel('t'), ylabel('u7');
figure;
subplot(4,2,1), plot((1:N)*h,uall(8,:)), hold on, plot((1:N)*h,us(8)*ones(1,N),'r'),xlabel('t'), ylabel('u8');
subplot(4,2,2), plot((1:N)*h,uall(9,:)), hold on, plot((1:N)*h,us(9)*ones(1,N),'r'),xlabel('t'), ylabel('u9');
subplot(4,2,3), plot((1:N)*h,uall(10,:)), hold on, plot((1:N)*h,us(10)*ones(1,N),'r'),xlabel('t'), ylabel('u10');
subplot(4,2,4), plot((1:N)*h,uall(11,:)), hold on, plot((1:N)*h,us(11)*ones(1,N),'r'),xlabel('t'), ylabel('u11');
subplot(4,2,5), plot((1:N)*h,uall(12,:)), hold on, plot((1:N)*h,us(12)*ones(1,N),'r'),xlabel('t'), ylabel('u12');
subplot(4,2,6), plot((1:N)*h,uall(13,:)), hold on, plot((1:N)*h,us(13)*ones(1,N),'r'),xlabel('t'), ylabel('u13');
subplot(4,2,7), plot((1:N)*h,uall(14,:)), hold on, plot((1:N)*h,us(14)*ones(1,N),'r'),xlabel('t'), ylabel('u14');
subplot(4,2,8), plot((1:N)*h,uall(15,:)), hold on, plot((1:N)*h,us(15)*ones(1,N),'r'),xlabel('t'), ylabel('u15');




end

