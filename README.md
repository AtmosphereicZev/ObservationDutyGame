# Observation Duty by Zev

Hey! I'm Zev and this is a little project i worked on for a month or two for my portfolio. if you are aware of the game "I'm on Observation Duty" its basically a clone of that with maybe a few things changed if even that. Unfortunately there isn't much content to the game other then just a singular map but I hope anyone who plays has fun nonetheless. I might in the future add more maps if I'm really feeling down for it but its very unlikely, if i do they will most likely be random map i pulled off FAB or something like that which would be in another branch other then "**release**" & "**dev**" so go check and see.

Take on a job at a Downtown Supermarket where employees have noticed strange things happening like objects vanishing, moving by themselves, and even seeing dark figures in the corner of their eyes. So we're taking it from here. Connect to the store's camera, spot the anomalies, and go home. 

You have 1 minute upon loading in the map before the first anomaly spawns, memorize the store and spot each anomaly after that. 1 anomaly spawns every minute, report whatever you see in the bottom left.

Something moved, rotated, or anything that changed in some way? = "**Object Manipulation**"
Notice an object that's not there anymore? = "**Object Disappearance**"
See an object that wasn't there before? = "**Extra Object**"
Camera seems off... by like a lot? = "**Camera Malfunction**"
Something dark on the floor but cant point out what? = "**Shadow**"

That's about it... have fun!
# Documentation

Here is Developer Documentation for anyone looking to mod/expand the game in some way, or perhaps review this code.

The entire project is made in C++ other then some UI elements so I'd recommend using Rider as an IDE when using Unreal but you can also use whatever your preference is.
## Setup

Setting up the project is basically non existent, you just need **Unreal Engine 5.7.4** installed and obviously **Visual Studio 2022 Version 17.8 or later** (with necessary components), you can either launch the engine and select "C++" when creating a new project and it will prompt you to install Visual Studio. Or you can follow [this](https://dev.epicgames.com/documentation/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine) article by epic if you need any more help. After just double click the uproject and everything should generate then open. 
## Creating a Map

The naming scheme for the current maps are a bit all over the place because there is currently only one map. But in the maps folder, `Main` is the Supermarket Level and `MainMenu` is well the main menu.

- All you need to do is right click in the maps folder and create a new Level. As long as there's no overriding game mode it should automatically be using `AODMainGameMode` and playing the level should work as normal.

- In `"Blueprints/Actors"` you should see `BP_MapCamera`, drag and drop the actor/pawn into the level for each camera you want in your map. Then select the camera you want the player controlling on startup, scroll down or search for "**Auto Activate for Player**" and set to `Player 0`. 

- Now when playing the map everything should be working! the intro screen will play, the player will automatically be controlling the camera you set to auto-possess, and they can switch to the other cameras in the map!.

Setting up the map selection and loading in from the Main Menu might take a little extra effort which in fairness is on me. So blame me if you run into any problems for my "crappy game"!!

- In `Blueprints/Widgets/LevelSelect` you should see a widget blueprint `WBP_LevelSelect`, double click on it and switch to Designer in the top right.

- Simply copy and paste **MapSelect1** and rename it to **MapSelect2** or whatever else. (make sure you paste it inside of the "Levels" grid box) and with your newly created button, highlight it in the Hierarchy and set the row and column to its correlated spot.

- Now switch to Graph in the top right. find the comment/box with the text "If another map is added, this is what that would look like." Control-Drag your button or "MapSelect" onto the graph and hook it up to the Set Nodes "Selected Button" pin. Also hook up the Set Nodes output pin to the "Set Background Color" nodes target pin.

- Click on your button or "MapSelect" again and scroll down in details to the events category, add the `OnPressed` event, then drag it up to the comment when it appears in the graph. Now drag its Exec pin to the set nodes Exec pin.

- Now set the `LevelName` and `LevelDesc` to fit your level, you should also set a thumbnail for your level. You can use the already made supermarket map above as a reference! 

- In the very top you should see an event named `Event Construct`, Click "Add Pin" on the "Make Array" node and drag your "MapSelect" onto it.

- Now your level shows up and is selectable but we still cant load into it, so now switch to ``Blueprints/Widgets/WBP_MainMenu`` and go to the graph then find the "Events" comment. Create a custom event and name it "Open (YOURLEVELNAME)". Create a `Open Level by Object Reference` node, hook it up to your event and select the map you created earlier. 

- Now switch back to designer and open the animations box in the bottom left, Duplicate `TransitionToSupermarket` and rename it to fit your own level. With the transition selected, in the events track right click the only keyframe and in the properties tab change the endpoint to your newly created Open (YOURLEVELNAME). 

- Now switch back to the graph and find the "On Connect" comment, add a pin to the switch on string node and edit that pin to your level name. Then copy and paste the "Play Animation" node and set the "in animation" pin to the animation you created.

Now you should be able to load and play your level starting from the Main Menu! Sorry if that was a bit convoluted, if you're at all experienced with unreal that should of been a breeze!

## Anomalies

Adding anomalies to your map should be WAY easier then creating one, everything is modular so this should be a blast. Any Static Mesh Actor you drag into your map can have anomalies, just select any actor you want to be anomalistic. Add the `Anomaly` Actor Component in the Details Panel and boom. Now just add any anomaly you want spawning in the Spawnable Anomalies tab. 
#### Spawnable Anomalies

Spawnable Anomalies on the `Anomaly` actor component is an array of FAnomaly(s), which is a struct that consist of the name, the type, the Camera the anomaly is associated with, and all actors the anomaly is associated with (which can sound confusing at first but will be explained), and the Anomaly Event which is what gets broadcasted when the anomaly actually gets triggered, but that isn't visible to the editor.

**Anomaly Name** - The name of the Anomaly you want spawning on the actor. The list of available anomalies can be found [[Observation Duty by Zev#^978eae||below]]
**Anomaly Type** - The type this anomaly is meant to be reported by in game.
**Associated Camera** - The camera this anomaly is meant to be seen/observed by. Can be easily set by using the eyedropper tool in the editor.
**Associated Actors** - Extra Functionality for certain anomalies, usage can be seen [[Observation Duty by Zev#^978eae||below]]



#### Available Anomalies ^978eae

| Anomaly Name | Anomaly Description                                                                                                                                                                  | Associated Actors Usage                  |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------- |
| Move         | Finds 2 mesh's with the "Mesh" tag then hides one and reveals the other. This is setup this way to make moving more precise in the editor.                                           |                                          |
| Vanish       | Changes the meshes visibility to false                                                                                                                                               | Changes each actors visibility to false. |
| VanishSprite | Same thing as Vanish, but for sprites.                                                                                                                                               |                                          |
| Appear       | Changes the meshes visibility to true.                                                                                                                                               | Changes each actors visibility to true.  |
| Shadow       | Shadows are sprites in the actual game, this should only be applied to a sprite and combined with the Shadow anomaly type. Just place a sprite down and set its visibility to false. |                                          |
| Malfunction  | Sets a Post Process Volume to active.                                                                                                                                                |                                          |


## Creating a Custom Anomaly

Creating a Custom Anomaly is simple enough. In the source go to `/ObservationDuty/Anomalies` and open `Anomaly.h` & `Anomaly.cpp`. In the header file create a function corresponding to the anomaly you want with the parameters (`UAnomalyComponent*, TArray<AActor*>, bool`)

- UAnomalyComponent - The component attached to the actor the anomaly is triggering for.
- TArray<AActor*> - The Associated Actors set in the Editor.
- bool - Whether the anomaly is being triggered or fixed.

Now inside `/ObservationDuty/Gamemodes/Gamestates` open `AODMainGameState.h` and find the Anomaly Functions Dictionary/Map. Add a new element with the name of your anomaly, and the function inside `Anomaly.h` associated with your anomaly. 

Should be formatted like this: `{"AnomalyName", FAnomalyDelegate::CreateStatic(&UAnomalies::AnomalyFunction)}`

That's it, now you should be able to use your anomaly in the editor.

## Creating a Custom Anomaly Type

Creating a Custom Anomaly Type meaning what you report in the bottom left of the screen is also pretty simple. In ``/ObservationDuty/Enums/EAnomalyTypes.h`` add another value with your anomaly type. Now in `/ObservationDuty/Gamemodes/Gamestates` open `AODMainGameState.h` and find the Anomaly Types Dictionary/Map then add a new element with the value you just created in EAnomalyTypes and how your type should appear in game.

Should be formatted like this: `{EAnomalyType, "AnomalyName"}` 

Done!

---

I think this project was a success and i hope you'd think so too! I am aware the UI isn't the most efficient to work around but other then that its pretty intuitive.

if it isn't already It'll soon be on on my site https://zevkun.dev and if you have any questions or feedback you can contact my socials connected to my GitHub account or via contact@zevkun.dev.

Thanks for checking it out!
