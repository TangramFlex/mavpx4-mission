# Tangram Maker MAV/PX4 Ground Control Station

This project demonstrates how to create a DIY ground control station (GCS) to fly a drone using free software tools. We'll show how to programmatically exchange MAVLink flight plan mission commands with a PX4 enabled drone using code auto-generated in Tangram Maker™.

Tangram Maker is a free cloud-hosted tool that can generate component software interfaces after simple menu selections, drag and drop, and the click of a button. Simplifying the process of creating the necessary communications code.

In the steps below we will use Tangram Maker to auto-generate a MAVLink interface in C++ that communicates with the PX4 software stack. Using an example C++ application and flight simulator, we'll fly a drone!

The drone mission in the example C++ application is simple (takeoff, waypoints, landing) to showcase how to use the generated MAVLink interface. It is possible to expand upon the drone commands and include additional logic. For those looking to go beyond "out of the box" drone control, such as QGroundControl, we hope this helps show what is possible and make the process easier for you.

*Tangram Maker has built-in support for MAVLink, ROS, and LMCP interface code generation. It also allows you to define your own custom messages, as well as transforms (mappings) between different messages. For more information see our tutorials [Author a Message Set with Flex](https://docs.tangramflex.io/docs/tutorials/flex_authorship) and [Author a Transform with Flex](https://docs.tangramflex.io/docs/tutorials/flex_transform)*.

## Getting Started

You'll need a free [**Tangram Maker**](https://tangramflex.com/tangram-maker) account to complete this project. [**Click here**](https://tangramflex.com/tangram-maker) to setup an account. 

Download and install [**VirtualBox**](https://www.virtualbox.org/). **Linux Ubuntu 20.04 LTS** is the supported environment to build and run this project. We'll be running  it on a virtual machine with VirtualBox. Download the [**Ubuntu 20.04 desktop image here**](https://releases.ubuntu.com/20.04.4/). Once you have VirtualBox installed and the Ubuntu image downloaded, follow this [**YouTube tutorial**](https://youtu.be/NFRzHQZSJvU) to complete your VM setup.


## Generating a MAVLink Interface in Tangram Maker 

Go to **https://maker.tangramflex.io/** and log in. Create a team if you haven't already: Go to **Teams** and click the **New Team** button.

In Tangram Maker, ***Components*** are the basic building blocks of a system. They are reusable elements that can stand alone as a single function or be connected with other components to extend capabilities. To model our MAVLink <> Drone system we'll create three components.

### Step 1: Create a Workspace Component

1. Go to the **Component Library** and click **New Component**
2. Enter the following details and click **Next**
    - Name: `MAVLinkWorkspace`
    - Category: `System`
    - Select your team
3. Click **Add Implementation**, enter name `v1`, and click **Create Implementation**
4. Click **Open Workspace**

You can think of your workspace as your top level component. For now, we are using the `MAVLinkWorkspace` component its implementation `v1` as a shell to house other components that you are about to create.

### Step 2: Create a GCS Component

Next we'll create a component to represent our ground control station (GCS).

1. Open the **Component Library** by clicking the box icon in the left menu 
2. Click **New Component**, enter the following details and click **Next**
    - Name: `MAVLinkGCS`
    - Category: `System`
    - Select your team
3. Click **Add Port** and select the **Message Set** called `MAVLink::v23`
4. Add the port configurations shown in the table below, clicking Add Port between each one. When selecting a message, you can type its name to filter the list.
   | Message            | Direction | Type |
   | ------------------ | --------- | ---- |
   | CommandLong        | Out       | Data |
   | MissionAck         | In        | Data |
   | MissionClearAll    | Out       | Data |
   | MissionCount       | Out       | Data |
   | MissionItem        | Out       | Data |
   | MissionRequest     | Out       | Data |
   | MissionRequestList | Out       | Data |
   | Heartbeat          | In-Out    | Data |
5. Click **Next** after all ports are configured
6. Enter **Implementation Name** `v1` and then click **Create Implementation**
7. Drag and drop it into the workspace

### Step 3: Create a Drone Component

Next we'll create a component to represent our drone.

1. Open the **Component Library** by clicking the box icon in the left menu
2. Click **New Component**, enter the following details and click **Next**
    - Name: `MAVLinkDrone`
    - Category: `System`
    - Select your team
3. Click **Add Port** and select the **Message Set** called `MAVLink::v23`
4. Add the port configurations shown in the table below, clicking Add Port between each one. When selecting a message, you can type its name to filter the list.
   | Message            | Direction | Type |
   | ------------------ | --------- | ---- |
   | CommandLong        | In        | Data |
   | MissionAck         | Out       | Data |
   | MissionClearAll    | In        | Data |
   | MissionCount       | In        | Data |
   | MissionItem        | In        | Data |
   | MissionRequest     | In        | Data |
   | MissionRequestList | In        | Data |
   | Heartbeat          | In-Out    | Data |
5. Click **Next** after all ports are configured
6. Enter **Implementation Name** `v1` and then click **Create Implementation**
7. Drag and drop it into the workspace

### Step 4: Connect Components

With two components now in your workspace, it's time to connect them up. This step will specify how these components talk with one another.

1. Click the **Make Connection** icon in the middle of the `MAVLinkGCS.v1` component, then click the same icon in the `MAVLinkDrone.v1` component to open the connections panel
2. Click **Show Suggested** in the top right, and then **Add All Suggested**
3. Click the **Done** button, or click back into the workspace to close the connections panel
4. Make sure to save the changes to your workspace, if it hasn't saved automatically

### Step 5: Generate MAVLink Interface Code

Now that you have a component based system design all wired up, it's time to to generate a *Component Software Interface* (CSI) - code that will allow components to pass the messages you specified to other components or systems. Tangram Maker's generated CSI is fully executable and saves you a ton of time, automatically creating the tedious communications code for you.

Next we'll open the MAVLinkGCS component and create a workflow to generate C++ code.

1. Open the MAVLinkGCS workspace by clicking the three dots in the `MAVLinkGCS.v1` component and then **Open New Tab**
2. Go to **Workflows** by clicking the list icon in the left menu
3. Click **New Workflow**, enter name: `Interface Code` and click **Create**
4. Wait a moment for it to appear, and then click on your new workflow
5. Click the blue **Tasks** button. This will show all the available plugins in Tangram Maker
6. Drag and drop the **`Code Gen 3.0`** plugin into the right area, then click its gear icon. Update the following settings:
    - Change the **Output Folder** to **`mavpx4-csi`**
    - Click Done
7.  Drag and drop the **`G++`** plugin into the right area, then click its gear icon. Update the following settings:
    - Select **Configuration** **`Makefile Compilation`**
    - Change **Make Directory** to **`mavpx4-csi`**
    - Change **Output folder** **`mavpx4-csi`**
    - Click Done
8. Now let's make a dependency between the two plugins to ensure the G++ task runs after Code Gen 3.0 completes
    - Click the connection icon in the **Code Gen 3.0** block
    - Then click in the middle of **G++** block (not on its connection icon)
    - You should now see line between the two plugins
9. Click **Save Changes** in the top right, and then **Close**
10. Now click **Run**!

The interface code generation and build process has begun! Streaming logs are shown while it runs, it'll take a few minutes to complete.

You can even close Tangram Maker and it will continue to run in the cloud. When the workflow is complete you'll be able to download its artifact file.

Let's hop over to the virtual machine while that runs.

## Setting Up PX4 In The Linux VM

We'll need to install the PX4 Autopilot software stack in our virtual machine. Follow the steps below or watch this [YouTube tutorial](https://www.youtube.com/watch?v=OtValQdAdrU).

1. Open VirtualBox and start your Linux Ubuntu 20.04 virtual machine
2. Open **Terminal** and run these commands:
    - `sudo apt-get install git` (type your password and press the enter key)
    - `git clone https://github.com/PX4/Firmware.git --recursive` 
    - `cd Firmware`
    - `bash ./Tools/setup/ubuntu.sh` (type your password and press the enter key)
3. Restart your virtual machine after the setup script completes
4. Open **Terminal** and run these commands:
    - `cd Firmware`
    - `make px4_sitl jmavsim` (this one takes a while the first time its run)
5. When it completes you should see a simulator open with a drone

## Setting up the MAVLink Interface and Mission

1. Open a new **Terminal** window and run these commands to clone this repo into your home folder:
    - `cd ~`
    - `git clone https://github.com/TangramFlex/mavpx4-mission.git`
2. Open **Firefox** (in the VM), go to **https://maker.tangramflex.io/** and log in to your account.
3. Go to the **Component Library**
4. Click on your `MAVLinkGCS` component, select the `v1` implementation and then **Open Workspace**
5. Go to **Workflows** by clicking the list icon in the left menu
6. Click on the workflow you created before and select the completed task
7. Download the code by clicking the disk "artifacts" icon on the **`G++`** task (not the Code Gen 3.0 one)
8.  Untar the downloaded artifact. It should be a folder named `mavpx4-csi`
9.  Move the `mavpx4-csi` folder to your home folder
10. Open it -- you'll see in its `src` folder all the necessary MAVLink C++ files -- but let's open the `test` folder
11. Drag the cloned `mavpx4-mission` folder into the `test` folder. So you should have a structure like `mavpx4-csi > test > mavpx4-mission`
12. Return to **Terminal** and enter these commands to build the mission app:
    - `cd mavpx4-csi/test/mavpx4-mission`
    - `make`

## Running It

Now you have a built `mission` app, the MAVLink GCS Interface ready to go, as well as the PX4 simulator running. Let's run the mission!

1. In **Terminal** enter the command: `./mission`
2. You should see the mission be received in the Terminal window that's running PX4, and then the drone take flight! 

The drone will take off, fly to three way points and then land.  

Note, if the mission fails to be received, try these steps:
1. Press Ctrl+C in both the mavpx4-mission and PX4 Terminal windows to cancel them
2. In the PX4 Terminal window enter `make px4_sitl jmavsim` to start the simulator again
3. In the mavpx4-mission Terminal window enter `./mission`

### Updating the Mission

Open the src `mission.cpp` file in the `mavpx4-csi/test/mavpx4-mission` folder. You'll see methods defining the MAVLink commands and instantiating the Tangram Maker MAVLink serializer. Scroll down to the main function. Here you'll see the 5 MAVLink commands that were sent to PX4. You can change the coordinates or add more way points.  If you do add more, update the mission count to match the number of commands you have. Return to the `mavpx4-mission` Terminal window, run `make` to build the updated app and then `./mission` to fly your new mission.