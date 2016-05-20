#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

namespace {
    const Size designResolutionSize_iPad = Size(512, 384);
    const Size designResolutionSize_iPhone = Size(568,320);
}

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("SpriteTest", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("SpriteTest");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    director->setProjection(Director::Projection::_2D);
    director->setDepthTest(false);
    
    Image::setPVRImagesHavePremultipliedAlpha(true);
    
    // Set the design resolution
    Size frameSize = glview->getFrameSize();
    CCLOG("frameSize = (%f,%f)",frameSize.width,frameSize.height);
    float height = frameSize.height;
    if (glview->isRetinaDisplay()) {
        CCLOG("is retina display");
        height /= 2;
    }
    
    if (height >= 600) {
        //iPad
        CCLOG("iPad");
        //_isIPad = true;
        glview->setDesignResolutionSize(designResolutionSize_iPad.width,
                                        designResolutionSize_iPad.height,
                                        ResolutionPolicy::NO_BORDER);
        director->setContentScaleFactor(2);
    } else {
        //iPhone
        CCLOG("iPhone");
        //_isIPad = false;
        glview->setDesignResolutionSize(designResolutionSize_iPhone.width,
                                        designResolutionSize_iPhone.height,
                                        ResolutionPolicy::NO_BORDER);
        director->setContentScaleFactor(2);
    }
    CCLOG("contentScaleFactor = %.0f",director->getContentScaleFactor());
    
    register_all_packages();
    
    std::vector<std::string> searchPath;
    searchPath.push_back("sprites");
    FileUtils::getInstance()->setSearchPaths(searchPath);
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("sprites.plist");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
