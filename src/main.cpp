#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelPage.hpp>
#include <map>

using namespace geode::prelude;

// new id -> original id (so name/face lookups still work after an id change)
static std::map<int, int> s_reverseIds;

static int faceToFrame(std::string const& f, bool& valid) {
    valid = true;
    if (f == "Auto") return -1;
    if (f == "N/A") return 0;
    if (f == "Easy") return 1;
    if (f == "Normal") return 2;
    if (f == "Hard") return 3;
    if (f == "Harder") return 4;
    if (f == "Insane") return 5;
    if (f == "Hard Demon") return 6;
    if (f == "Easy Demon") return 7;
    if (f == "Medium Demon") return 8;
    if (f == "Insane Demon") return 9;
    if (f == "Extreme Demon") return 10;
    valid = false; // "Default"
    return 0;
}

static void applyFace(GJDifficultySprite* spr, int origId) {
    if (!spr || origId < 1 || origId > 22) return;
    auto face = Mod::get()->getSettingValue<std::string>(fmt::format("face-{}", origId));
    bool valid;
    int frame = faceToFrame(face, valid);
    if (valid) spr->updateDifficultyFrame(frame, GJDifficultyName::Long);
}

static int origIdOf(int id) {
    auto it = s_reverseIds.find(id);
    return it != s_reverseIds.end() ? it->second : id;
}

class $modify(GameLevelManager) {
    GJGameLevel* getMainLevel(int id, bool dontGetLevelString) {
        auto level = GameLevelManager::getMainLevel(id, dontGetLevelString);
        if (!level || id < 1 || id > 22) return level;

        auto name = Mod::get()->getSettingValue<std::string>(fmt::format("name-{}", id));
        if (!name.empty()) level->m_levelName = name;

        // WARNING: changing the id can affect completion/stat tracking
        auto newId = Mod::get()->getSettingValue<int64_t>(fmt::format("id-{}", id));
        if (newId > 0) {
            s_reverseIds[(int)newId] = id;
            level->m_levelID = (int)newId;
        }
        return level;
    }
};

class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;
        if (level && level->m_levelType == GJLevelType::Local)
            applyFace(m_difficultySprite, origIdOf(level->m_levelID));
        return true;
    }
};

class $modify(LevelPage) {
    void updateDynamicPage(GJGameLevel* level) {
        LevelPage::updateDynamicPage(level);
        if (level) applyFace(m_difficultySprite, origIdOf(level->m_levelID));
    }
};
