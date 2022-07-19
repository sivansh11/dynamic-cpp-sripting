## Dynamic C++ Module
// seperate from engine

Platform independent (main targets are windows and linux, might work for mac also, but thats not my target lol)
Maps script src to the so/dll file (both are paths)
Should have some form of way to detect changes in file (either use of some external library like qfilesystemwatcher or a custom solution ie hashing)
Ability to retrive functions from lib
System commands to compile changed src files
Ability to manually reload and the option to reload all at every interval

## Script Component  
// part of engine 

Integrates the Dynamic C++ Module to the engine

All scripts will inherit from a virtual class (not purely virtual, all functions will have empty definitions)
It will have the following functions:
- OnCreate()
- OnUpdate()
- OnRender()
- OnImGuiRender() // for editor panel stuff
- OnDestroy()

# Things I need to figure out
A way to allow user to create custom components without adding them to engines core components (done)
A way to give access to current scene and self. (done)
(the entity attached to the script need not be a physical entity but may just be present to perform some computation on all other entities)


### EDIT -- NEW IDEAS
- distinction between entity scripts and system sctripts
- entity scripts manage their own data (no ecs accept a refrence to self)
- system scripts uses ecs to manage data, they are not provoked by any entity, but is called by the engine itself 

### TODO
add register component to ecs 
- assignes the component an ID and addes it to the component pools

