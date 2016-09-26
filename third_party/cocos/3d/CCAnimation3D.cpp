/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "3d/CCAnimation3D.h"
#include "3d/CCBundle3D.h"
#define CC_SAFE_RELEASE_NULL(x) {if (NULL != (x)) x->decRef();x=NULL;}
#define CC_SAFE_DELETE(x) {if (NULL!=(x)) delete x;}
#define CC_SAFE_RELEASE(x) {if (NULL != (x)) x->decRef();}

Animation3D::Curve* Animation3D::getBoneCurveByName(const std::string& name) const
{
    auto it = _boneCurves.find(name);
    if (it != _boneCurves.end())
        return it->second;
    
    return nullptr;
}

Animation3D::Animation3D()
: _duration(0)
{
    
}

Animation3D::~Animation3D()
{
    for (auto itor : _boneCurves) {
        CC_SAFE_DELETE(itor.second);
    }
}

Animation3D::Curve::Curve()
: translateCurve(nullptr)
, rotCurve(nullptr)
, scaleCurve(nullptr)
{
    
}
Animation3D::Curve::~Curve()
{
    CC_SAFE_RELEASE_NULL(translateCurve);
    CC_SAFE_RELEASE_NULL(rotCurve);
    CC_SAFE_RELEASE_NULL(scaleCurve);
}

bool Animation3D::init(const Animation3DData &data)
{
    _duration = data._totalTime;

    for(const auto& iter : data._translationKeys)
    {
        Curve* curve = _boneCurves[iter.first];
        if( curve == nullptr)
        {
            curve = new (std::nothrow) Curve();
            _boneCurves[iter.first] = curve;
        }
        
        if(iter.second.size() == 0) continue;
        std::vector<float> keys;
        std::vector<float> values;
        for(const auto& keyIter : iter.second)
        {
            keys.push_back(keyIter._time);
            values.push_back(keyIter._key.x);
            values.push_back(keyIter._key.y);
            values.push_back(keyIter._key.z);
        }
        
        curve->translateCurve = AnimationCurve::create(&keys[0], &values[0], (int)keys.size(), 3);
    }
    
    for(const auto& iter : data._rotationKeys)
    {
        Curve* curve = _boneCurves[iter.first];
        if( curve == nullptr)
        {
            curve = new (std::nothrow) Curve();
            _boneCurves[iter.first] = curve;
        }
        
        if(iter.second.size() == 0) continue;
        std::vector<float> keys;
        std::vector<float> values;
        for(const auto& keyIter : iter.second)
        {
            keys.push_back(keyIter._time);
            values.push_back(keyIter._key.x);
            values.push_back(keyIter._key.y);
            values.push_back(keyIter._key.z);
            values.push_back(keyIter._key.w);
        }
        
        curve->rotCurve = AnimationCurve::create(&keys[0], &values[0], (int)keys.size(), 4);
    }
    
    for(const auto& iter : data._scaleKeys)
    {
        Curve* curve = _boneCurves[iter.first];
        if( curve == nullptr)
        {
            curve = new (std::nothrow) Curve();
            _boneCurves[iter.first] = curve;
        }
        
        if(iter.second.size() == 0) continue;
        std::vector<float> keys;
        std::vector<float> values;
        for(const auto& keyIter : iter.second)
        {
            keys.push_back(keyIter._time);
            values.push_back(keyIter._key.x);
            values.push_back(keyIter._key.y);
            values.push_back(keyIter._key.z);
        }
        
        curve->scaleCurve = AnimationCurve::create(&keys[0], &values[0], (int)keys.size(), 3);
    }
    
    return true;
}

////////////////////////////////////////////////////////////////
Animation3DCache* Animation3DCache::_cacheInstance = nullptr;

Animation3DCache* Animation3DCache::getInstance()
{
    if (_cacheInstance == nullptr)
        _cacheInstance = new (std::nothrow) Animation3DCache();
    
    return _cacheInstance;
}
void Animation3DCache::destroyInstance()
{
    CC_SAFE_DELETE(_cacheInstance);
}

Animation3D* Animation3DCache::getAnimation(const std::string& key)
{
    auto it = _animations.find(key);
    if (it != _animations.end())
        return it->second;
    return nullptr;
}

void Animation3DCache::addAnimation(const std::string& key, Animation3D* animation)
{
    const auto& it = _animations.find(key);
    if (it != _animations.end())
    {
        return; // already have this key
    }
    _animations[key] = animation;
    animation->addRef();
}

void Animation3DCache::removeAllAnimations()
{
    for (auto itor : _animations) {
        CC_SAFE_RELEASE(itor.second);
    }
    _animations.clear();
}
Animation3DCache::Animation3DCache()
{
    
}
Animation3DCache::~Animation3DCache()
{
    removeAllAnimations();
}

