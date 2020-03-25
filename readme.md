GEANT 4 Tutorial for the rest of Group 14

I hope all the following is clear and makes sense, if not let me know - Ira

Login and Set-Up

To login to the UCL High Energy Physics cluster use the following commands in the Terminal/Command Prompt:

ssh -Y ishokar@plus1.hep.ucl.ac.uk
(password:) ******** (you won’t be able to see what you are typing, don’t worry about this)

(The first time you do this something will come up asking yes/no, you should type: yes)

ssh -Y ishokar@pc202.hep.ucl.ac.uk
(password:) ********

(To run SL6 rather than CentOS7 for Dawn: ssh -X ishokar@pc195.hep.ucl.ac.uk)

To set up the environment enter:

source /unix/local/Geant4/Geant4-10.4.0-Linux/bin/geant4.sh
(To run SL6 rather than CentOS7 for Dawn: source /unix/pbt/software/scripts/pbt.sh or source /unix/pbt/software/scripts/eb-centos7/pbt.sh)


Navigating Linux

To find the directory with the source code enter the change directory (cd) command:

cd GEANT4

To see the files in the directory, type the list (ls) command (note this is a lowercase letter L, not a number 1) :

ls 

You will see 3 directories: GeBoulbyFolder  HPGeFolder  PhotonPBFolder.
GeBoulbyFolder - the source code from Prof. Ghag from the Boulby Germanium detector experiment
HPGeFolder - the code we are editing to try and simulate the HPGe detector in the lab
PhotonPBFolder- an example of successfully a GEANT4 simulation for a proton beam

To navigate the HPGe experiment we are working on:

cd HPGeFolder

Then

ls

You will see two directories: HPGe_build  HPGe_source.
HPGe_build - the directory in which our simulation is being run in
HPGe_source-  the directory in which our source code is contained and it is in here that we will need to edit files to match our detector, before running the simulation within the HPGe_build directory

To navigate the HPGe_source directory:
 
cd HPGe_source

Then

ls

Here you will see the files that can also be found in the google drive under the GEANT4 folder:

build.sh  CMakeLists.txt  CMakeLists.txt~  Ge.cc  GNUmakefile  include  inter.mac  README.md  src  vis.mac:

We are interested in altering the C++ files in the directory src:

cd src

Then

ls

These are the files that we will alter to simulate our detector, rather than the one at Boulby that the code currently simulates, 

GeActionInitialization.cc  GeDetectorMessenger.cc  GeHit.cc          GePhysicsListMessenger.cc  GePhysListParticles.cc       GeRunAction.cc     GeSample.cc          GeDetector.cc              GeEventAction.cc        GeMaterials.cc    GePhysListHadron.cc        GePMT.cc                     GeRun.cc           GeSD.cc         GeDetectorConstruction.cc  GeHistoManager.cc       GePhysicsList.cc  GePhysListHadron.cc~       GePrimaryGeneratorAction.cc        GeRunMessenger.cc      GeShielding.cc

To look at one of these files use emacs text editor:

emacs <filename.cc> (eg. emacs GeDetectorConstruction.cc)

To close emacs:

Ctrl-x Ctrl-c then type y (yes) or n (no) when met with do you want to save anything, if you have edited the files

To navigate back to the HPGeFolder enter:

cd /home/ishokar/GEANT4/HPGeFolder/HPGe_build_new 

(alternatively, you can repeatedly go back on the directory using cd .. until you are again in the same directory)

To compile the code from the source file enter:

source /unix/local/Geant4/Geant4-10.4.0-Linux/bin/geant4.sh
cmake -DGeant4_DIR=/unix/pbt/software/dev /home/ishokar/GEANT4/HPGeFolder
Make

/vis/viewer/set/viewpointThetaPhi 70 20.

Run the simulation

To navigate back to the HPGeFolder enter:
cd /home/ishokar/GEANT4/HPGeFolder/HPGe_build_new 

To run:
./Ge 

cmake -DGeant4_DIR=/unix/pbt/software/dev /home/ishokar/GEANT4/B4c

cmake -DGeant4_DIR=/unix/pbt/software/dev /home/ishokar/GEANT4/B4Folder/B4c

/vis/viewer/set/viewpointThetaPhi 45 270
/gps/energy 100 MeV
/gps/pos/type Volume
/gps/pos/shape Cylinder
/gps/pos/centre 0 0 36 cm
/gps/pos/radius 30 cm
/gps/pos/halfz 5 cm
/gps/ang/type iso
/run/beamOn 10

/gps/position 0 0 36 cm
/gps/particle gamma
/gps/ang/type iso
/gps/ene/type Gauss
/gps/ene/mono 1200 keV
/gps/ene/sigma 4.6 keV
/run/beamOn 5000



/gps/ene/mono 662.2 keV
/gps/ene/sigma 2.4 keV

/gps/ene/mono 400.1 keV
/gps/ene/sigma 1.5 keV

/gps/ene/mono 1461.5 keV
/gps/ene/sigma 2.8 keV

/gps/ene/mono 905.4 keV
/gps/ene/sigma 2.6 keV

/gps/ene/mono 1074.0 keV
/gps/ene/sigma 2.7 keV


https://www.ortec-online.com/-/media/ametekortec/technical%20papers/high%20purity%20germanium%20detector%20applications%20and%20technology%20developements/best-choice-high-purity-germanium-hpge-detector.pdf?la=en


References:

GEANT4 PhotonPB tutorial 
http://www.hep.ucl.ac.uk/pbt/wiki/Software/Geant4/Tutorials/Basic/Monoenergetic_Photon_Pencil_Beam

GEANT4 User Documentation
http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/fo/Geant4InstallationGuide.pdf

Germanium Boulby experiment
https://www.sciencedirect.com/science/article/pii/S0927650517302517?via%3Dihub

B4 Calorimeter Example
http://geant4-userdoc.web.cern.ch/geant4-userdoc/Doxygen/examples_doc/html/ExampleB4.html






