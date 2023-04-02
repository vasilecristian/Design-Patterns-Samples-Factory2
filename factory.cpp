#include <iostream>


/* Create Platform factory, that can create support for different platforms.
*
*   Platform is a factory that can create different implementations for each platform. The IPlatform is an interface .
*
*   This Example have an issue with the enum class PlatformType. The SOLID principle is 
*   not meet (aka Open for extension Closed for modifications principle) since when you want 
*   to extent the enum by adding new types of platforms the enum must be changed.
*   
*   Instead, enum i have used class with static members. When you want to add more platforms
*   is enough to use inheritance (derive the Platforms class) and create a new Factory function
*   that handle the new types (along with the old types).
*
*/

class IPlatform
{
public:
    virtual ~IPlatform() = default;
    virtual std::string ToString() = 0;
};

class iOS : public IPlatform
{
    std::string ToString()
    {
        return "iOS";
    }
};

class Android : public IPlatform
{
    std::string ToString()
    {
        return "Android";
    }
};

class XBox : public IPlatform
{
    std::string ToString()
    {
        return "XBox";
    }
};

class Steam : public IPlatform
{
    std::string ToString()
    {
        return "Steam";
    }
};

//---------------------------------------
// Define the Platforms

//enum class PlatformType: int
//{
//    iOS,
//    Android,
//    XBox,
//    Steam
//};

typedef int PlatformType;

class Platforms
{
public:
    static const PlatformType iOS = 1;
    static const PlatformType Android = 2;

    static const PlatformType Last = Android;
};

/** Factory Function Design pattern*/
IPlatform* CreatePlatform(PlatformType hotDrinkType)
{
    switch(hotDrinkType)
    {
        case Platforms::iOS:
            return new iOS();

        case Platforms::Android:
            return new Android();

        default:
            return nullptr;
    }
}
//---------------------------------------


//---------------------------------------
// Extended the Factory function design pattern ....

class ExtendedPlatforms : public Platforms
{
public:
    static const PlatformType XBox = Platforms::Last + 1;
    static const PlatformType Steam = Platforms::Last + 2;
};

/** This is used to extend the Platform Factory Function design pattern*/
IPlatform* CreatePlatformExtended(PlatformType hotDrinkType)
{
    switch(hotDrinkType)
    {
        case ExtendedPlatforms::XBox:
            return new XBox();

        case ExtendedPlatforms::Steam:
            return new Steam();
        
        default:
            return CreatePlatform(hotDrinkType);
    }

    return nullptr;
}
//---------------------------------------




int main()
{
    std::cout << "Sample for Factory Method Design Pattern!" << std::endl;

    IPlatform* platform1 = CreatePlatformExtended(ExtendedPlatforms::iOS);
    std::cout << "Platform 1: " <<  platform1->ToString() << std::endl;
    
    IPlatform* platform2 = CreatePlatformExtended(ExtendedPlatforms::Android);
    std::cout << "Platform 2: " <<  platform2->ToString() << std::endl;

    IPlatform* platform3 = CreatePlatformExtended(ExtendedPlatforms::XBox);
    std::cout << "Platform 3: " <<  platform3->ToString() << std::endl;

    IPlatform* platform4 = CreatePlatformExtended(ExtendedPlatforms::Steam);
    std::cout << "Platform 4: " <<  platform4->ToString() << std::endl;

    return 0;
}