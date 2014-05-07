=OpenRump=

An open source physics based sex game.

==Branches==
* Please checkout the branch **devel**, and branch off your
  work from there. The commands for that are as follows.
    $ git checkout devel
    $ git checkout -b topicname
  Make sure to give your branch a suitable name (depending
  on what you're working on).

* All merges into devel must compile and run successfully.

* All merges into master must be stable on all platforms.

==Prerequisits==
* You need a C++0x or C++11 compliant compiler in order
  to be able to compile this project.

* You will need CMake 2.8.11 or later in order to be able
  to generate project files for this project.

* You must manually copy your shared library build of
  "RenderSystem GL" to the folder "res/plugins". This
  file is built when you build (or download a prebuilt
  version of) Ogre3D.

* Assets are not part of the project due to copyright
  limitations. They are loaded externally from one
  directory level above the root directory in a folder
  called "openrump-assets" when building in debug.
  You can obtain a copy of these files from the
  project leader via e-mailing: liquidbuffer@gmail.com

* It is recommended to build and install the dependencies
  into the folder "dep/build" rather than installing them
  globally.  The build system will be able to pick on them.
  - NOTE: Build system is currently fucked.


