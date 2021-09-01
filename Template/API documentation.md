General Notes
The base Class of everything in the engine is GameObject. You can inherit from Gameobject using 
DisplayObject and show a still image for the object using the TextureManager. If you want to Animate
the object inherit from the Sprite Class which inherits from DisplayObject which inherits from GameObject. You
can use Sprite and the TextureManager to slice up sprite sheets using data from a .txt file to create 
animations. You have to build these animations as you can see in the Player class. The GameObject Class 
has three pure virtual functions which the child classes can override. These are update, draw and clean.
As you can see Player, Sprite and DisplayObject all have virtual update, draw and clean Classes so any of those 
Classes override those 3 functions. In this way the engine calls update and draw every frame on every DisplayObject
in a vector of DisplayObjects using a loop within the current Scene. clean can be called from a Scene when the game 
is being quit to call the destructors of every DisplayObject in the list of DisplayObjects. DisplayObject is also used 
to store the DisplayObjects order in layer and which Scene the DisplayObject is in or parented by. Sometimes throughout 
the comments I use object to describe something as an instance of a Class. Just understand that object is a general 
programming term and GameObject is a more game dev related term which I am using to describe the specific GameObject 
Class in this engine. The GameObject Class sets whether the GameObject is visible or enabled. It also has the structs 
Transform and Rigidbody which are used to set and get data for movement and collision. The CollisionManager contains a 
bunch of functions that can be used for a variety of different types of collision between objects. The CollisionManager 
uses different functions from The Util Class which is filled with math related functions which you can use in other 
parts of your code as well. The Managers are either static like the CollisionManager or Singletons like the SoundManager 
so you have global access to those Classes for ease of use. The main loop of the game is run from main.cpp which calls 
functions from the Singleton Class Game which has a Type Definition or typedef so it is called using TheGame. Another 
thing I want to mention is IMGUI. Using IMGUI you can debug using UI that lets you adjusts values such as position 
during runtime. You can see the initial code for IMGUI in the PlayScene. Press ` to open it at runtime. Read through 
the documentation in the IMGUI folder. Explore to find ways that IMGUI can help and speed up your development. There 
is also enums which you can use by using #include "THE_ENUM.h". An example of this is in the GameObject Class it uses 
GameObjectType.h to store what type of GameObject the GameObject is. Make sure to explore the whole engine and try
to understand the relationships between everything. You can right click anything and use find all references to check 
what code is being used by what. It might be helpful to open a program like paint or lucid charts online and to 
reverse engineer the engine and all its connections using UML or whatever works for you. Enjoy your semester!