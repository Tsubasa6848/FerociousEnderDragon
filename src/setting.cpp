#include <llapi/utils/FileHelper.h>
#include <Nlohmann/json.hpp>
#include <LoggerAPI.h>

extern Logger logger;
extern bool isDragonAlive;

#define TRJ(key1, key2, val)                                     \
    if (json.find(key1) != json.end())                           \
    {                                                            \
        if (json.at(key1).find(key2) != json.at(key1).end())     \
        {                                                        \
            const nlohmann::json &out2 = json.at(key1).at(key2); \
            out2.get_to(val);                                    \
        }                                                        \
    }

namespace Settings
{
    bool ModifyDragonHealth = true;
    int DragonHealth = 2000;
    bool AttackCrystalOnly = true;
    bool ModifyCrystalExplosion = true;
    bool CrystalExplosionFire = true;
    int CrystalExplosionPower = 20;
    bool ModifyDragonDamage = true; 
    int DragonBreathDamage = 15;
    int DirectAttackDamage = 45;
    bool PlayerDamageLimit = true;
    int MaxDamagePerTime = 20;
    bool ImmuneDamageWhileLanding = true;
    bool IfCrystalHeal = true;
    int HealCostTime = 120;
    bool DragonExplosion = true;//
    int DragonExplosionPower = 6;
    bool DragonLightning = true;
    int LightningDamage = 20;
    bool ReflectDamage = true;
    float ReflectPercentage = 20;
    bool SpawnChildMob = true;
    std::vector<std::string> ChildMobList = {
        "minecraft:warden"
    };
    bool NatureRegeneration = false;
    int IntervalTicks = 20;
    int RegenerationEachTime = 1;
    nlohmann::ordered_json globaljson()
    {
        nlohmann::ordered_json json;
        json["ModifyDragonHealth"]["Enabled"] = ModifyDragonHealth;
        json["ModifyDragonHealth"]["DragonHealth"] = DragonHealth;
        json["AttacktoDestroyCrystalOnly"]["Enabled"] = AttackCrystalOnly;
        json["ModifyCrystalExplosion"]["Enabled"] = ModifyCrystalExplosion;
        json["ModifyCrystalExplosion"]["isFire"] = CrystalExplosionFire;
        json["ModifyCrystalExplosion"]["Power"] = CrystalExplosionPower;
        json["ModifyDragonDamage"]["Enabled"] = ModifyDragonDamage;
        json["ModifyDragonDamage"]["DragonBreathDamage"] = DragonBreathDamage;
        json["ModifyDragonDamage"]["DirectAttackDamage"] = DirectAttackDamage;
        json["PlayerDamageLimit"]["Enabled"] = PlayerDamageLimit;
        json["PlayerDamageLimit"]["MaxDamagePerTime"] = MaxDamagePerTime;
        json["ImmuneDamageWhileLanding"]["Enabled"] = ImmuneDamageWhileLanding;
        json["CrystalRegeneration"]["Enabled"] = IfCrystalHeal;
        json["CrystalRegeneration"]["Time"] = HealCostTime;
        json["DragonExplosion"]["Enabled"] = DragonExplosion;
        json["DragonExplosion"]["Power"] = DragonExplosionPower;
        json["DragonLightning"]["Enabled"] = DragonLightning;
        json["DragonLightning"]["Power"] = LightningDamage;
        json["ReflectDamage"]["Enabled"] = ReflectDamage;
        json["ReflectDamage"]["Percentage"] = ReflectPercentage;
        json["SpawnChildMobs"]["Enabled"] = SpawnChildMob;
        json["SpawnChildMobs"]["ChildMobList"] = ChildMobList;
        json["DragonNatureRegeneration"]["Enabled"] = NatureRegeneration;
        json["DragonNatureRegeneration"]["IntervalTicks"] = IntervalTicks;
        json["DragonNatureRegeneration"]["RegenerationEachTime"] = RegenerationEachTime;
        return json;
    }

    void initjson(nlohmann::json json)
    {
        TRJ("DragonAttribute", "Enabled", ModifyDragonHealth);
        TRJ("DragonAttribute", "DragonHealth", DragonHealth);
        TRJ("AttacktoDestroyCrystalOnly", "Enabled", AttackCrystalOnly);
        TRJ("ModifyCrystalExplosion", "Enabled", ModifyCrystalExplosion);
        TRJ("ModifyCrystalExplosion", "isFire", CrystalExplosionFire);
        TRJ("ModifyCrystalExplosion", "Power", CrystalExplosionPower);
        TRJ("ModifyDragonDamage", "Enabled", ModifyDragonDamage);
        TRJ("ModifyDragonDamage", "DragonBreathDamage", DragonBreathDamage);
        TRJ("ModifyDragonDamage", "DirectAttackDamage", DirectAttackDamage);
        TRJ("PlayerDamageLimit", "Enabled", PlayerDamageLimit);
        TRJ("PlayerDamageLimit", "MaxDamagePerTime", MaxDamagePerTime);
        TRJ("ImmuneDamageWhileLanding", "Enabled", ImmuneDamageWhileLanding);
        TRJ("CrystalRegeneration", "Enabled", IfCrystalHeal);
        TRJ("CrystalRegeneration", "Time", HealCostTime);
        TRJ("DragonExplosion", "Enabled", DragonExplosion);
        TRJ("DragonExplosion", "Power", DragonExplosionPower);
        TRJ("DragonLightning", "Enabled", DragonLightning);
        TRJ("DragonLightning", "Power", LightningDamage);
        TRJ("ReflectDamage", "Enabled", ReflectDamage);
        TRJ("ReflectDamage", "Percentage", ReflectPercentage);
        TRJ("SpawnChildMobs", "Enabled", SpawnChildMob);
        TRJ("SpawnChildMobs", "ChildMobList", ChildMobList);
        TRJ("DragonNatureRegeneration", "Enabled", NatureRegeneration);
        TRJ("DragonNatureRegeneration", "IntervalTicks", IntervalTicks);
        TRJ("DragonNatureRegeneration", "RegenerationEachTime", RegenerationEachTime);
    }

    void WriteDefaultConfig(const std::string &fileName)
    {
        std::ofstream file(fileName);
        if (!file.is_open())
        {
            logger.error("Fail to open config file!");
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string &fileName)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            logger.error("Fail to open config file!");
            return;
        }
        nlohmann::ordered_json json;
        file >> json;
        file.close();
        initjson(json);
        WriteDefaultConfig(fileName);
    }
    void reloadJson(const std::string &fileName)
    {
        std::ofstream file(fileName);
        if (file)
        {
            file << globaljson().dump(4);
        }
        else
        {
            logger.error("Error in config file!");
        }
        file.close();
    }
}

void IniData() {
    if(!std::filesystem::exists("plugins/FerociousEnderDragon/data.json")){
        std::ofstream DefaultFile("plugins/FerociousEnderDragon/data.json");
        if (!DefaultFile.is_open()) {
            return;
        }
        nlohmann::json json;
        json.clear();
        json["isDragonAlive"] = false;
        DefaultFile << json.dump(4);
        DefaultFile.close();
    }
}

void loadConfig() { 
    if (!std::filesystem::exists("plugins/FerociousEnderDragon")){
        std::filesystem::create_directories("plugins/FerociousEnderDragon");	
    }
    if (std::filesystem::exists("plugins/FerociousEnderDragon/config.json")) {
        Settings::LoadConfigFromJson("plugins/FerociousEnderDragon/config.json");
    }
    else {
        logger.warn("Config file does not exist, created automatically.");
        Settings::WriteDefaultConfig("plugins/FerociousEnderDragon/config.json");
    }
    IniData();
}