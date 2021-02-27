# uClinux_arm_cortexm

I write a socket program on uClinux to test my kernel modification.<br>
If you want to test it, you may need to follow the steps below:

- ### Linux development environment
  - bash$ cd uClinux_arm_cortexm/ 
  - bash$ . ACTIVATE.sh 
  - bash$ cd projects/my_developer 
  - bash$ make

- ### Board load uClinux image via TFTP in U-Boot mode
  - M2S-COM> setenv ipaddr <strong>yourip</strong>
  - M2S-COM> setenv serverip <strong>serverip</strong>
  - M2S-COM> setenv image my_developer.uImage
  - M2S-COM> run update
  - M2S-SOM> reset

  And if you can see the following, means you have successfully make it work :<br><br>
  resetting ...<br>
  U-Boot 2010.03-linux-cortexm-1.9.1 (Jan 23 2013 - 17:19:37)<br>
  ...<br>
  Starting kernel ...<br>
  ...<br>
  init started: BusyBox v1.17.0 (Jan 23 2013 - 17:21:30)<br>
  ~ # 
  
- ### Run my_developer project
  ~ # insmod sample.ko<br>
  ~ # ./app
