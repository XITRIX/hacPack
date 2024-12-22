#include <iostream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <map>
#include <cstdlib>
#include "nacp.hpp"
#include "utils.hpp"
#include "tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

void nacp_tool::print(const string *input_filepath)
{
    nacp_t nacp;

    // Read NACP
    ifstream nacp_file(*input_filepath, ifstream::binary | ifstream::in);
    if (nacp_file.fail())
    {
        cerr << "Failed to open " << *input_filepath << "\n";
        exit(EXIT_FAILURE);
    }

    // Check file size
    nacp_file.seekg(0, ios::end);
    uint32_t nacp_file_size = nacp_file.tellg();
    if (nacp_file_size != sizeof(nacp_t))
    {
        cerr << "Invalid file: " << *input_filepath << "\n";
        exit(EXIT_FAILURE);
    }

    // Read file
    nacp_file.seekg(0, ios::beg);
    nacp_file.read((char *)&nacp, sizeof(nacp_t));
    nacp_file.close();

    //Print ApplicationTitle info
    cout << "Application Title:\n";
    for (int titlec = 0; titlec < 16; titlec++)
    {
        if (nacp.Title[titlec].Name[0] != '\0' || nacp.Title[titlec].Publisher[0] != '\0')
            cout << nacp_tool::get_title_lang_name(titlec) << ":\n"
                 << "Name: " << nacp.Title[titlec].Name << "\nPublisher: " << nacp.Title[titlec].Publisher << "\n\n";
    }

    // Print Supported Language Flag
    cout << "Supported Language Flag:\n";
    bitset<32> slfc_bits(nacp.SupportedLanguageFlag);
    for (int slfc = 0; slfc < 16; slfc++)
    {
        if (slfc_bits.test(slfc))
            cout << get_title_lang_name(slfc) << "\n";
    }

    // Print Rating Age
    cout << "\nRating Age:\n";
    for (int ratingc = 0; ratingc < 32; ratingc++)
    {
        if (nacp.RatingAge[ratingc] != 0xFF)
            cout << std::dec << nacp_tool::get_rating_age_organization_name(ratingc) << ": " << (unsigned)nacp.RatingAge[ratingc] << "\n";
    }

    cout << "\n";

    //Print Local Communication Id
    cout << "Local Communication id:\n";
    for (int lcidc = 0; lcidc < 8; lcidc++)
        cout << "Local Communication id " << lcidc + 1 << ": 0x" << std::hex << std::setfill('0') << std::setw(16) << (unsigned)nacp.LocalCommunicationId[lcidc] << "\n";

    cout << "\n";

    //Print Play Log Queryable Application Id
    cout << "Play Log Queryable Application id:\n";
    for (int plqaidc = 0; plqaidc < 8; plqaidc++)
        cout << "Play Log Queryable Application id " << plqaidc + 1 << ": 0x" << std::hex << std::setfill('0') << std::setw(16) << (unsigned)nacp.PlayLogQueryableApplicationId[plqaidc] << "\n";

    cout << "\n";
    cout << "Play Log Policy: " << nacp_tool::get_play_log_policy(nacp.PlayLogPolicy) << "\n";
    cout << "Play Log Query Capability: " << nacp_tool::get_play_log_query_capability(nacp.PlayLogQueryCapability) << "\n";
    cout << "\n";
    cout << "SaveData Owner id: 0x" << std::hex << std::setfill('0') << std::setw(16) << nacp.SaveDataOwnerId << "\n";
    cout << "Presence Group id: 0x" << std::hex << std::setfill('0') << std::setw(16) << nacp.PresenceGroupId << "\n";
    cout << "Seed For PseudoDevice id: 0x" << std::hex << std::setfill('0') << std::setw(16) << nacp.SeedForPseudoDeviceId << "\n";
    cout << "\n";
    cout << "Application ErrorCode Category: " << nacp.ApplicationErrorCodeCategory << "\n";
    cout << "Isbn: " << nacp.Isbn << "\n";
    cout << "Bcat Passphrase: " << nacp.BcatPassphrase << "\n";
    cout << "Bcat Delivery Cache Storage Size: " << std::dec << nacp.BcatDeliveryCacheStorageSize << "\n";
    cout << "\n";
    cout << "UserAccount SaveData Size: " << std::dec << nacp.UserAccountSaveDataSize << "\n";
    cout << "UserAccount SaveData Size Max: " << std::dec << nacp.UserAccountSaveDataSizeMax << "\n";
    cout << "UserAccount SaveData Journal Size: " << std::dec << nacp.UserAccountSaveDataJournalSize << "\n";
    cout << "UserAccount SaveData Journal Size Max: " << std::dec << nacp.UserAccountSaveDataJournalSizeMax << "\n";
    cout << "Device SaveData Size: " << std::dec << nacp.DeviceSaveDataSize << "\n";
    cout << "Device SaveData Size Max: " << std::dec << nacp.DeviceSaveDataSizeMax << "\n";
    cout << "Device SaveData Journal Size: " << std::dec << nacp.DeviceSaveDataJournalSize << "\n";
    cout << "Device SaveData Journal Size Max: " << std::dec << nacp.DeviceSaveDataJournalSizeMax << "\n";
    cout << "Cache Storage Size: " << std::dec << nacp.CacheStorageSize << "\n";
    cout << "Cache Storage Journal Size: " << std::dec << nacp.CacheStorageJournalSize << "\n";
    cout << "Cache Storage Data And Journal Size Max: " << std::dec << nacp.CacheStorageDataAndJournalSizeMax << "\n";
    cout << "Cache Storage Index Max: " << std::dec << nacp.CacheStorageIndexMax << "\n";
    cout << "Temporary Storage Size: " << std::dec << nacp.TemporaryStorageSize << "\n";
    cout << "\n";
    cout << "AddOnContent Base id: 0x" << std::hex << std::setfill('0') << std::setw(16) << nacp.AddOnContentBaseId << "\n";
    cout << "AddOnContent Registration Type: " << nacp_tool::get_addoncontent_registration_type(nacp.AddOnContentRegistrationType) << "\n";
    cout << "Runtime AddOnContent Install : " << nacp_tool::get_runtime_addoncontent_install(nacp.RuntimeAddOnContentInstall) << "\n";
    cout << "\n";
    cout << "Attribute Flag: " << nacp_tool::get_attribute_flag(nacp.AttributeFlag) << "\n";
    cout << "ParentalControl Flag: " << nacp_tool::get_parental_control_flag(nacp.ParentalControlFlag) << "\n";
    cout << "Repair Flag: " << nacp_tool::get_repair_flag(nacp.RepairFlag) << "\n";
    cout << "\n";
    cout << "Display Version: " << nacp.DisplayVersion << "\n";
    cout << "Logo Type: " << nacp_tool::get_logo_type(nacp.LogoType) << "\n";
    cout << "Logo Handling: " << nacp_tool::get_logo_handling(nacp.LogoHandling) << "\n";
    cout << "Startup User Account: " << nacp_tool::get_startup_user_account(nacp.StartupUserAccount) << "\n";
    cout << "Startup User Account Option Flag: " << nacp_tool::get_startup_user_account_option_flag(nacp.StartupUserAccountOptionFlag) << "\n";
    cout << "UserAccount Switch Lock: " << nacp_tool::get_useraccount_switch_lock(nacp.UserAccountSwitchLock) << "\n";
    cout << "Required Network Service License On Launch: " << nacp_tool::get_required_network_service_license_on_launch(nacp.RequiredNetworkServiceLicenseOnLaunchFlag) << "\n";
    cout << "Screenshot: " << nacp_tool::get_screenshot(nacp.Screenshot) << "\n";
    cout << "Videocapture: " << nacp_tool::get_videocapture(nacp.VideoCapture) << "\n";
    cout << "HDCP: " << nacp_tool::get_hdcp(nacp.Hdcp) << "\n";
    cout << "\n";
    cout << "DataLoss Confirmation: " << nacp_tool::get_dataloss_confirmation(nacp.DataLossConfirmation) << "\n";
    cout << "Crash Report : " << nacp_tool::get_crash_report(nacp.CrashReport) << "\n";
    cout << "Program Index: " << std::dec << (unsigned)nacp.ProgramIndex << "\n";
}

void nacp_tool::createxml(const string *input_filepath, const string *output_filepath)
{
    nacp_t nacp;

    // Read NACP
    cout << "Reading " << *input_filepath << "\n";
    ifstream nacp_file(*input_filepath, ifstream::binary | ifstream::in);
    if (nacp_file.fail())
    {
        cerr << "Failed to open " << *input_filepath << "\n";
        exit(EXIT_FAILURE);
    }

    // Check file size
    nacp_file.seekg(0, ios::end);
    uint32_t nacp_file_size = nacp_file.tellg();
    if (nacp_file_size != sizeof(nacp_t))
    {
        cerr << "Invalid file: " << *input_filepath << "\n";
        exit(EXIT_FAILURE);
    }

    // Read file
    nacp_file.seekg(0, ios::beg);
    nacp_file.read((char *)&nacp, sizeof(nacp_t));
    nacp_file.close();

    // Parse NACP
    cout << "Parsing " << *input_filepath << "\n";
    XMLDocument nacp_xml;
    XMLDeclaration *decl = nacp_xml.NewDeclaration("xml version=\"1.0\" encoding=\"utf-8\"");
    nacp_xml.InsertFirstChild(decl);
    nacp_xml.SetBOM(true);
    XMLNode *xml_nApplication = nacp_xml.NewElement("Application");
    nacp_xml.InsertEndChild(xml_nApplication);

    // ApplicationTitle
    for (int titlec = 0; titlec < 16; titlec++)
    {
        if (nacp.Title[titlec].Name[0] != '\0' || nacp.Title[titlec].Publisher[0] != '\0')
        {
            XMLElement *xml_eTitle = nacp_xml.NewElement("Title");
            xml_nApplication->InsertEndChild(xml_eTitle);
            XMLElement *xml_eTitle_Language = nacp_xml.NewElement("Language");
            xml_eTitle_Language->SetText(nacp_tool::get_title_lang_name(titlec));
            xml_eTitle->InsertEndChild(xml_eTitle_Language);
            XMLElement *xml_eTitle_Name = nacp_xml.NewElement("Name");
            xml_eTitle_Name->SetText(nacp.Title[titlec].Name);
            xml_eTitle->InsertEndChild(xml_eTitle_Name);
            XMLElement *xml_eTitle_Publisher = nacp_xml.NewElement("Publisher");
            xml_eTitle_Publisher->SetText(nacp.Title[titlec].Publisher);
            xml_eTitle->InsertEndChild(xml_eTitle_Publisher);
        }
    }

    XMLElement *xml_eIsbn = nacp_xml.NewElement("Isbn");
    if (nacp.Isbn[0] != '\0')
        xml_eIsbn->SetText(nacp.Isbn);
    xml_nApplication->InsertEndChild(xml_eIsbn);
    XMLElement *xml_eStartupUserAccount = nacp_xml.NewElement("StartupUserAccount");
    xml_eStartupUserAccount->SetText(nacp_tool::get_startup_user_account(nacp.StartupUserAccount));
    xml_nApplication->InsertEndChild(xml_eStartupUserAccount);
    XMLElement *xml_eUserAccountSwitchLock = nacp_xml.NewElement("UserAccountSwitchLock");
    xml_eUserAccountSwitchLock->SetText(nacp_tool::get_useraccount_switch_lock(nacp.UserAccountSwitchLock));
    xml_nApplication->InsertEndChild(xml_eUserAccountSwitchLock);
    XMLElement *xml_eParentalControl = nacp_xml.NewElement("ParentalControl");
    xml_eParentalControl->SetText(nacp_tool::get_parental_control_flag(nacp.ParentalControlFlag));
    xml_nApplication->InsertEndChild(xml_eParentalControl);

    // SupportedLanguage
    bitset<32> slfc_bits(nacp.SupportedLanguageFlag);
    for (int slfc = 0; slfc < 16; slfc++)
    {
        if (slfc_bits.test(slfc))
        {
            XMLElement *xml_eSupportedLanguage = nacp_xml.NewElement("SupportedLanguage");
            xml_eSupportedLanguage->SetText(nacp_tool::get_title_lang_name(slfc));
            xml_nApplication->InsertEndChild(xml_eSupportedLanguage);
        }
    }

    XMLElement *xml_eScreenshot = nacp_xml.NewElement("Screenshot");
    xml_eScreenshot->SetText(nacp_tool::get_screenshot(nacp.Screenshot));
    xml_nApplication->InsertEndChild(xml_eScreenshot);
    XMLElement *xml_eVideoCapture = nacp_xml.NewElement("VideoCapture");
    xml_eVideoCapture->SetText(nacp_tool::get_videocapture(nacp.VideoCapture));
    xml_nApplication->InsertEndChild(xml_eVideoCapture);
    XMLElement *xml_ePresenceGroupId = nacp_xml.NewElement("PresenceGroupId");
    string strPresenceGroupId = uint_to_hex(nacp.PresenceGroupId);
    xml_ePresenceGroupId->SetText(strPresenceGroupId.c_str());
    xml_nApplication->InsertEndChild(xml_ePresenceGroupId);
    XMLElement *xml_eDisplayVersion = nacp_xml.NewElement("DisplayVersion");
    xml_eDisplayVersion->SetText(nacp.DisplayVersion);
    xml_nApplication->InsertEndChild(xml_eDisplayVersion);

    // Rating
    for (int ratingc = 0; ratingc < 32; ratingc++)
    {
        if (nacp.RatingAge[ratingc] != 0xFF)
        {
            XMLElement *xml_eRating = nacp_xml.NewElement("Rating");
            xml_nApplication->InsertEndChild(xml_eRating);
            XMLElement *xml_eRating_Organization = nacp_xml.NewElement("Organization");
            xml_eRating_Organization->SetText(get_rating_age_organization_name(ratingc));
            xml_eRating->InsertEndChild(xml_eRating_Organization);
            XMLElement *xml_eRating_Age = nacp_xml.NewElement("Age");
            xml_eRating_Age->SetText(nacp.RatingAge[ratingc]);
            xml_eRating->InsertEndChild(xml_eRating_Age);
        }
    }

    XMLElement *xml_eDataLossConfirmation = nacp_xml.NewElement("DataLossConfirmation");
    xml_eDataLossConfirmation->SetText(nacp_tool::get_dataloss_confirmation(nacp.DataLossConfirmation));
    xml_nApplication->InsertEndChild(xml_eDataLossConfirmation);
    XMLElement *xml_ePlayLogPolicy = nacp_xml.NewElement("PlayLogPolicy");
    xml_ePlayLogPolicy->SetText(nacp_tool::get_play_log_policy(nacp.PlayLogPolicy));
    xml_nApplication->InsertEndChild(xml_ePlayLogPolicy);
    XMLElement *xml_eSaveDataOwnerId = nacp_xml.NewElement("SaveDataOwnerId");
    string strSaveDataOwnerId = uint_to_hex(nacp.SaveDataOwnerId);
    xml_eSaveDataOwnerId->SetText(strSaveDataOwnerId.c_str());
    xml_nApplication->InsertEndChild(xml_eSaveDataOwnerId);
    XMLElement *xml_eUserAccountSaveDataSize = nacp_xml.NewElement("UserAccountSaveDataSize");
    string strUserAccountSaveDataSize = uint_to_hex(nacp.UserAccountSaveDataSize);
    xml_eUserAccountSaveDataSize->SetText(strUserAccountSaveDataSize.c_str());
    xml_nApplication->InsertEndChild(xml_eUserAccountSaveDataSize);
    XMLElement *xml_eUserAccountSaveDataJournalSize = nacp_xml.NewElement("UserAccountSaveDataJournalSize");
    string strUserAccountSaveDataJournalSize = uint_to_hex(nacp.UserAccountSaveDataJournalSize);
    xml_eUserAccountSaveDataJournalSize->SetText(strUserAccountSaveDataJournalSize.c_str());
    xml_nApplication->InsertEndChild(xml_eUserAccountSaveDataJournalSize);
    XMLElement *xml_eDeviceSaveDataSize = nacp_xml.NewElement("DeviceSaveDataSize");
    string strDeviceSaveDataSize = uint_to_hex(nacp.DeviceSaveDataSize);
    xml_eDeviceSaveDataSize->SetText(strDeviceSaveDataSize.c_str());
    xml_nApplication->InsertEndChild(xml_eDeviceSaveDataSize);
    XMLElement *xml_eDeviceSaveDataJournalSize = nacp_xml.NewElement("DeviceSaveDataJournalSize");
    string strDeviceSaveDataJournalSize = uint_to_hex(nacp.DeviceSaveDataJournalSize);
    xml_eDeviceSaveDataJournalSize->SetText(strDeviceSaveDataJournalSize.c_str());
    xml_nApplication->InsertEndChild(xml_eDeviceSaveDataJournalSize);
    XMLElement *xml_eBcatDeliveryCacheStorageSize = nacp_xml.NewElement("BcatDeliveryCacheStorageSize");
    string strBcatDeliveryCacheStorageSize = uint_to_hex(nacp.BcatDeliveryCacheStorageSize);
    xml_eBcatDeliveryCacheStorageSize->SetText(strBcatDeliveryCacheStorageSize.c_str());
    xml_nApplication->InsertEndChild(xml_eBcatDeliveryCacheStorageSize);
    XMLElement *xml_eApplicationErrorCodeCategory = nacp_xml.NewElement("ApplicationErrorCodeCategory");
    if (nacp.ApplicationErrorCodeCategory[0] != '\0')
        xml_eApplicationErrorCodeCategory->SetText(nacp.ApplicationErrorCodeCategory);
    xml_nApplication->InsertEndChild(xml_eApplicationErrorCodeCategory);
    XMLElement *xml_eAddOnContentBaseId = nacp_xml.NewElement("AddOnContentBaseId");
    string strAddOnContentBaseId = uint_to_hex(nacp.AddOnContentBaseId);
    xml_eAddOnContentBaseId->SetText(strAddOnContentBaseId.c_str());
    xml_nApplication->InsertEndChild(xml_eAddOnContentBaseId);
    XMLElement *xml_eLogoType = nacp_xml.NewElement("LogoType");
    xml_eLogoType->SetText(nacp_tool::get_logo_type(nacp.LogoType));
    xml_nApplication->InsertEndChild(xml_eLogoType);
    XMLElement *xml_eLocalCommunicationId = nacp_xml.NewElement("LocalCommunicationId");
    string strLocalCommunicationId = uint_to_hex(nacp.LocalCommunicationId[0]);
    xml_eLocalCommunicationId->SetText(strLocalCommunicationId.c_str());
    xml_nApplication->InsertEndChild(xml_eLocalCommunicationId);
    XMLElement *xml_eLogoHandling = nacp_xml.NewElement("LogoHandling");
    xml_eLogoHandling->SetText(nacp_tool::get_logo_handling(nacp.LogoHandling));
    xml_nApplication->InsertEndChild(xml_eLogoHandling);
    XMLElement *xml_eSeedForPseudoDeviceId = nacp_xml.NewElement("SeedForPseudoDeviceId");
    string strSeedForPseudoDeviceId = uint_to_hex(nacp.SeedForPseudoDeviceId);
    xml_eSeedForPseudoDeviceId->SetText(strSeedForPseudoDeviceId.c_str());
    xml_nApplication->InsertEndChild(xml_eSeedForPseudoDeviceId);
    XMLElement *xml_eBcatPassphrase = nacp_xml.NewElement("BcatPassphrase");
    if (nacp.BcatPassphrase[0] != '\0')
        xml_eBcatPassphrase->SetText(nacp.BcatPassphrase);
    xml_nApplication->InsertEndChild(xml_eBcatPassphrase);
    XMLElement *xml_eStartupUserAccountOption = nacp_xml.NewElement("StartupUserAccountOption");
    xml_eStartupUserAccountOption->SetText(nacp_tool::get_startup_user_account_option_flag(nacp.StartupUserAccountOptionFlag));
    xml_nApplication->InsertEndChild(xml_eStartupUserAccountOption);
    XMLElement *xml_eAddOnContentRegistrationType = nacp_xml.NewElement("AddOnContentRegistrationType");
    xml_eAddOnContentRegistrationType->SetText(nacp_tool::get_addoncontent_registration_type(nacp.AddOnContentRegistrationType));
    xml_nApplication->InsertEndChild(xml_eAddOnContentRegistrationType);
    XMLElement *xml_eUserAccountSaveDataSizeMax = nacp_xml.NewElement("UserAccountSaveDataSizeMax");
    string strUserAccountSaveDataSizeMax = uint_to_hex(nacp.UserAccountSaveDataSizeMax);
    xml_eUserAccountSaveDataSizeMax->SetText(strUserAccountSaveDataSizeMax.c_str());
    xml_nApplication->InsertEndChild(xml_eUserAccountSaveDataSizeMax);
    XMLElement *xml_eUserAccountSaveDataJournalSizeMax = nacp_xml.NewElement("UserAccountSaveDataJournalSizeMax");
    string strUserAccountSaveDataJournalSizeMax = uint_to_hex(nacp.UserAccountSaveDataJournalSizeMax);
    xml_eUserAccountSaveDataJournalSizeMax->SetText(strUserAccountSaveDataJournalSizeMax.c_str());
    xml_nApplication->InsertEndChild(xml_eUserAccountSaveDataJournalSizeMax);
    XMLElement *xml_eDeviceSaveDataSizeMax = nacp_xml.NewElement("DeviceSaveDataSizeMax");
    string strDeviceSaveDataSizeMax = uint_to_hex(nacp.DeviceSaveDataSizeMax);
    xml_eDeviceSaveDataSizeMax->SetText(strDeviceSaveDataSizeMax.c_str());
    xml_nApplication->InsertEndChild(xml_eDeviceSaveDataSizeMax);
    XMLElement *xml_eDeviceSaveDataJournalSizeMax = nacp_xml.NewElement("DeviceSaveDataJournalSizeMax");
    string strDeviceSaveDataJournalSizeMax = uint_to_hex(nacp.DeviceSaveDataJournalSizeMax);
    xml_eDeviceSaveDataJournalSizeMax->SetText(strDeviceSaveDataJournalSizeMax.c_str());
    xml_nApplication->InsertEndChild(xml_eDeviceSaveDataJournalSizeMax);
    XMLElement *xml_eTemporaryStorageSize = nacp_xml.NewElement("TemporaryStorageSize");
    string strTemporaryStorageSize = uint_to_hex(nacp.TemporaryStorageSize);
    xml_eTemporaryStorageSize->SetText(strTemporaryStorageSize.c_str());
    xml_nApplication->InsertEndChild(xml_eTemporaryStorageSize);
    XMLElement *xml_eCacheStorageSize = nacp_xml.NewElement("CacheStorageSize");
    string strCacheStorageSize = uint_to_hex(nacp.CacheStorageSize);
    xml_eCacheStorageSize->SetText(strCacheStorageSize.c_str());
    xml_nApplication->InsertEndChild(xml_eCacheStorageSize);
    XMLElement *xml_eCacheStorageJournalSize = nacp_xml.NewElement("CacheStorageJournalSize");
    string strCacheStorageJournalSize = uint_to_hex(nacp.CacheStorageJournalSize);
    xml_eCacheStorageJournalSize->SetText(strCacheStorageJournalSize.c_str());
    xml_nApplication->InsertEndChild(xml_eCacheStorageJournalSize);
    XMLElement *xml_eCacheStorageDataAndJournalSizeMax = nacp_xml.NewElement("CacheStorageDataAndJournalSizeMax");
    string strCacheStorageDataAndJournalSizeMax = uint_to_hex(nacp.CacheStorageDataAndJournalSizeMax);
    xml_eCacheStorageDataAndJournalSizeMax->SetText(strCacheStorageDataAndJournalSizeMax.c_str());
    xml_nApplication->InsertEndChild(xml_eCacheStorageDataAndJournalSizeMax);
    XMLElement *xml_eCacheStorageIndexMax = nacp_xml.NewElement("CacheStorageIndexMax");
    string strCacheStorageIndexMax = uint_to_hex(nacp.CacheStorageIndexMax);
    xml_eCacheStorageIndexMax->SetText(strCacheStorageIndexMax.c_str());
    xml_nApplication->InsertEndChild(xml_eCacheStorageIndexMax);
    XMLElement *xml_eHdcp = nacp_xml.NewElement("Hdcp");
    xml_eHdcp->SetText(nacp_tool::get_hdcp(nacp.Hdcp));
    xml_nApplication->InsertEndChild(xml_eHdcp);
    XMLElement *xml_eCrashReport = nacp_xml.NewElement("CrashReport");
    xml_eCrashReport->SetText(nacp_tool::get_crash_report(nacp.CrashReport));
    xml_nApplication->InsertEndChild(xml_eCrashReport);
    XMLElement *xml_eRuntimeAddOnContentInstall = nacp_xml.NewElement("RuntimeAddOnContentInstall");
    xml_eRuntimeAddOnContentInstall->SetText(nacp_tool::get_runtime_addoncontent_install(nacp.RuntimeAddOnContentInstall));
    xml_nApplication->InsertEndChild(xml_eRuntimeAddOnContentInstall);
    XMLElement *xml_ePlayLogQueryableApplicationId = nacp_xml.NewElement("PlayLogQueryableApplicationId");
    string strPlayLogQueryableApplicationId = uint_to_hex(nacp.PlayLogQueryableApplicationId[0]);
    xml_ePlayLogQueryableApplicationId->SetText(strPlayLogQueryableApplicationId.c_str());
    xml_nApplication->InsertEndChild(xml_ePlayLogQueryableApplicationId);
    XMLElement *xml_ePlayLogQueryCapability = nacp_xml.NewElement("PlayLogQueryCapability");
    xml_ePlayLogQueryCapability->SetText(nacp_tool::get_play_log_query_capability(nacp.PlayLogQueryCapability));
    xml_nApplication->InsertEndChild(xml_ePlayLogQueryCapability);
    XMLElement *xml_eRepair = nacp_xml.NewElement("Repair");
    xml_eRepair->SetText(nacp_tool::get_repair_flag(nacp.RepairFlag));
    xml_nApplication->InsertEndChild(xml_eRepair);
    XMLElement *xml_eAttribute = nacp_xml.NewElement("Attribute");
    xml_eAttribute->SetText(nacp_tool::get_attribute_flag(nacp.AttributeFlag));
    xml_nApplication->InsertEndChild(xml_eAttribute);
    XMLElement *xml_eProgramIndex = nacp_xml.NewElement("ProgramIndex");
    xml_eProgramIndex->SetText(nacp.ProgramIndex);
    xml_nApplication->InsertEndChild(xml_eProgramIndex);
    XMLElement *xml_eRequiredNetworkServiceLicenseOnLaunch = nacp_xml.NewElement("RequiredNetworkServiceLicenseOnLaunch");
    xml_eRequiredNetworkServiceLicenseOnLaunch->SetText(nacp_tool::get_required_network_service_license_on_launch(nacp.RequiredNetworkServiceLicenseOnLaunchFlag));
    xml_nApplication->InsertEndChild(xml_eRequiredNetworkServiceLicenseOnLaunch);

    // Save XML
    cout << "Saving " << *output_filepath << "\n";
    if (nacp_xml.SaveFile(output_filepath->c_str()) == XMLError::XML_SUCCESS)
        cout << "Saved XML file to: " << *output_filepath << "\n";
    else
    {
        cerr << "Failed to write " << *output_filepath << "\n";
        exit(EXIT_FAILURE);
    }
}

void nacp_tool::createnacp(const string *input_filepath, const string *output_filepath)
{
    nacp_t nacp = {};

    // Load XML
    cout << "Reading " << *input_filepath << "\n";
    XMLDocument nacp_xml;
    if (nacp_xml.LoadFile(input_filepath->c_str()) != XMLError::XML_SUCCESS)
    {
        cerr << "Failed to open " << *input_filepath << "\n";
        exit(EXIT_FAILURE);
    }

    // Parse XML
    cout << "Parsing " << *input_filepath << "\n";
    XMLNode *nApplicaiton = nacp_xml.FirstChildElement("Application");
    if (nApplicaiton == nullptr)
    {
        cerr << *input_filepath << " is not a xml file \n";
        exit(EXIT_FAILURE);
    }

    // Initialize rating age
    for (int ratingc = 0; ratingc < 32; ratingc++)
        nacp.RatingAge[ratingc] = 0xFF;

    bitset<32> slfc_bits;
    string strElement;
    XMLElement *eElement = nApplicaiton->FirstChildElement();
    while (eElement != nullptr)
    {
        strElement = string(eElement->Value());
        if (strElement == "Title")
        {
            int lang_id;
            XMLElement *eTitle;
            eTitle = eElement->FirstChildElement("Language");
            if (eTitle == nullptr)
            {
                cerr << "<Language> Element is not present in <Title> \n";
                exit(EXIT_FAILURE);
            }
            if (eTitle->GetText() != NULL)
                lang_id = nacp_tool::get_title_lang_id(eTitle->GetText());
            else
            {
                cerr << "Value of <Language> element is empty\n";
                exit(EXIT_FAILURE);
            }
            eTitle = eElement->FirstChildElement("Name");
            if (eTitle == nullptr)
            {
                cerr << "<Name> Element is not present in <Title> \n";
                exit(EXIT_FAILURE);
            }
            if (eTitle->GetText() == NULL)
            {
                cerr << "Value of <Name> element is empty\n";
                exit(EXIT_FAILURE);
            }
            if (strlen(eTitle->GetText()) > 512)
            {
                cerr << "Value of <Name> element is longer than 512 characters\n";
                exit(EXIT_FAILURE);
            }
            strncpy(nacp.Title[lang_id].Name, eTitle->GetText(), strlen(eTitle->GetText()));
            eTitle = eElement->FirstChildElement("Publisher");
            if (eTitle == nullptr)
            {
                cerr << "<Publisher> Element is not present in <Title> \n";
                exit(EXIT_FAILURE);
            }
            if (eTitle->GetText() == NULL)
            {
                cerr << "Value of <Publisher> element is empty\n";
                exit(EXIT_FAILURE);
            }
            if (strlen(eTitle->GetText()) > 256)
            {
                cerr << "Value of <Publisher> element is longer than 512 characters\n";
                exit(EXIT_FAILURE);
            }
            strncpy(nacp.Title[lang_id].Publisher, eTitle->GetText(), strlen(eTitle->GetText()));
        }
        else if (strElement == "Isbn")
        {
            if (eElement->GetText() != NULL)
            {
                if (strlen(eElement->GetText()) <= 37)
                    strncpy(nacp.Isbn, eElement->GetText(), strlen(eElement->GetText()));
                else
                {
                    cerr << "Value of <Isbn> element is longer than 37 characters\n";
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (strElement == "StartupUserAccountOption")
        {
            if (eElement->GetText() != NULL)
                nacp.StartupUserAccountOptionFlag = nacp_tool::set_startup_user_account_option_flag(eElement->GetText());
            else
            {
                cerr << "Value of <StartupUserAccountOption> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "StartupUserAccount")
        {
            if (eElement->GetText() != NULL)
                nacp.StartupUserAccount = nacp_tool::set_startup_user_account(eElement->GetText());
            else
            {
                cerr << "Value of <StartupUserAccount> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "UserAccountSwitchLock")
        {
            if (eElement->GetText() != NULL)
                nacp.UserAccountSwitchLock = nacp_tool::set_useraccount_switch_lock(eElement->GetText());
            else
            {
                cerr << "Value of <UserAccountSwitchLock> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "ParentalControl")
        {
            if (eElement->GetText() != NULL)
                nacp.ParentalControlFlag = nacp_tool::set_parental_control_flag(eElement->GetText());
            else
            {
                cerr << "Value of <ParentalControl> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "SupportedLanguage")
        {
            if (eElement->GetText() != NULL)
                slfc_bits.set(nacp_tool::get_title_lang_id(eElement->GetText()));
            else
            {
                cerr << "Value of <SupportedLanguage> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "Screenshot")
        {
            if (eElement->GetText() != NULL)
                nacp.Screenshot = nacp_tool::set_screenshot(eElement->GetText());
            else
            {
                cerr << "Value of <Screenshot> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "VideoCapture")
        {
            if (eElement->GetText() != NULL)
                nacp.VideoCapture = nacp_tool::set_videocapture(eElement->GetText());
            else
            {
                cerr << "Value of <VideoCapture> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "PresenceGroupId")
        {
            if (eElement->GetText() != NULL)
            {
                errno = 0;
                nacp.PresenceGroupId = strtoull(eElement->GetText(), NULL, 16);
                if (nacp.PresenceGroupId < 0x0100000000000000 || nacp.PresenceGroupId > 0x01ffffffffffffff || errno == ERANGE)
                {
                    cerr << "Value of <PresenceGroupId> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <PresenceGroupId> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "DisplayVersion")
        {
            if (eElement->GetText() != NULL)
            {
                if (strlen(eElement->GetText()) <= 16)
                    strncpy(nacp.DisplayVersion, eElement->GetText(), strlen(eElement->GetText()));
                else
                {
                    cerr << "Value of <DisplayVersion> element is longer than 16 characters\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <DisplayVersion> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "Rating")
        {
            int rating_id;
            XMLElement *eRating;
            eRating = eElement->FirstChildElement("Organization");
            if (eRating == nullptr)
            {
                cerr << "<Organization> Element is not present in <Rating> \n";
                exit(EXIT_FAILURE);
            }
            if (eRating->GetText() != NULL)
                rating_id = nacp_tool::get_rating_age_organization_id(eRating->GetText());
            else
            {
                cerr << "Value of <Organization> element is empty\n";
                exit(EXIT_FAILURE);
            }
            eRating = eElement->FirstChildElement("Age");
            if (eRating == nullptr)
            {
                cerr << "<Age> Element is not present in <Rating> \n";
                exit(EXIT_FAILURE);
            }
            if (eRating->GetText() != NULL)
            {
                try
                {
                    nacp.RatingAge[rating_id] = stoi(eRating->GetText(), NULL, 10);
                }
                catch (exception &e)
                {
                    cerr << "Value of <Age> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <Age> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "DataLossConfirmation")
        {
            if (eElement->GetText() != NULL)
                nacp.DataLossConfirmation = nacp_tool::set_dataloss_confirmation(eElement->GetText());
            else
            {
                cerr << "Value of <DataLossConfirmation> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "PlayLogPolicy")
        {
            if (eElement->GetText() != NULL)
                nacp.PlayLogPolicy = nacp_tool::set_play_log_policy(eElement->GetText());
            else
            {
                cerr << "Value of <PlayLogPolicy> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "SaveDataOwnerId")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.SaveDataOwnerId = strtoull(eElement->GetText(), NULL, 16);
                if (nacp.SaveDataOwnerId < 0x0100000000000000 || nacp.SaveDataOwnerId > 0x01ffffffffffffff || errno == ERANGE)
                {
                    cerr << "Value of <SaveDataOwnerId> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <SaveDataOwnerId> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "UserAccountSaveDataSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.UserAccountSaveDataSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <UserAccountSaveDataSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <UserAccountSaveDataSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "UserAccountSaveDataJournalSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.UserAccountSaveDataJournalSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <UserAccountSaveDataJournalSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <UserAccountSaveDataJournalSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "DeviceSaveDataSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.DeviceSaveDataSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <DeviceSaveDataSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <DeviceSaveDataSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "DeviceSaveDataJournalSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.DeviceSaveDataJournalSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <DeviceSaveDataJournalSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <DeviceSaveDataJournalSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "BcatDeliveryCacheStorageSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.BcatDeliveryCacheStorageSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <BcatDeliveryCacheStorageSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <BcatDeliveryCacheStorageSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "ApplicationErrorCodeCategory")
        {
            if (eElement->GetText() != NULL)
            {
                if (strlen(eElement->GetText()) <= 8)
                    strncpy(nacp.ApplicationErrorCodeCategory, eElement->GetText(), strlen(eElement->GetText()));
                else
                {
                    cerr << "Value of <ApplicationErrorCodeCategory> element is longer than 8 characters\n";
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (strElement == "AddOnContentBaseId")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.AddOnContentBaseId = strtoull(eElement->GetText(), NULL, 16);
                if (nacp.AddOnContentBaseId < 0x0100000000000000 || nacp.SaveDataOwnerId > 0x01ffffffffffffff || errno == ERANGE)
                {
                    cerr << "Value of <AddOnContentBaseId> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <AddOnContentBaseId> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "LogoType")
        {
            if (eElement->GetText() != NULL)
                nacp.LogoType = nacp_tool::set_logo_type(eElement->GetText());
            else
            {
                cerr << "Value of <LogoType> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "LocalCommunicationId")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.LocalCommunicationId[0] = strtoull(eElement->GetText(), NULL, 16);
                if (nacp.LocalCommunicationId[0] < 0x0100000000000000 || nacp.SaveDataOwnerId > 0x01ffffffffffffff || errno == ERANGE)
                {
                    cerr << "Value of <LocalCommunicationId> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
                for (int lcidc = 1; lcidc < 8; lcidc++)
                    nacp.LocalCommunicationId[lcidc] = nacp.LocalCommunicationId[0];
            }
            else
            {
                cerr << "Value of <LocalCommunicationId> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "LogoHandling")
        {
            if (eElement->GetText() != NULL)
                nacp.LogoHandling = nacp_tool::set_logo_handling(eElement->GetText());
            else
            {
                cerr << "Value of <LogoHandling> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "SeedForPseudoDeviceId")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.SeedForPseudoDeviceId = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <SeedForPseudoDeviceId> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <SeedForPseudoDeviceId> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "BcatPassphrase")
        {
            if (eElement->GetText() != NULL)
            {
                if (strlen(eElement->GetText()) <= 65)
                    strncpy(nacp.BcatPassphrase, eElement->GetText(), strlen(eElement->GetText()));
                else
                {
                    cerr << "Value of <BcatPassphrase> element is longer than 65 characters\n";
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (strElement == "AddOnContentRegistrationType")
        {
            if (eElement->GetText() != NULL)
                nacp.AddOnContentRegistrationType = nacp_tool::set_addoncontent_registration_type(eElement->GetText());
            else
            {
                cerr << "Value of <AddOnContentRegistrationType> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "UserAccountSaveDataSizeMax")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.UserAccountSaveDataSizeMax = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <UserAccountSaveDataSizeMax> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <UserAccountSaveDataSizeMax> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "UserAccountSaveDataJournalSizeMax")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.UserAccountSaveDataJournalSizeMax = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <UserAccountSaveDataJournalSizeMax> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <UserAccountSaveDataJournalSizeMax> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "DeviceSaveDataSizeMax")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.DeviceSaveDataSizeMax = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <DeviceSaveDataSizeMax> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <DeviceSaveDataSizeMax> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "DeviceSaveDataJournalSizeMax")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.DeviceSaveDataJournalSizeMax = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <DeviceSaveDataJournalSizeMax> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <DeviceSaveDataJournalSizeMax> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "TemporaryStorageSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.TemporaryStorageSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <TemporaryStorageSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <TemporaryStorageSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "CacheStorageSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.CacheStorageSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <CacheStorageSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <CacheStorageSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "CacheStorageJournalSize")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.CacheStorageJournalSize = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <CacheStorageJournalSize> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <CacheStorageJournalSize> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "CacheStorageDataAndJournalSizeMax")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.CacheStorageDataAndJournalSizeMax = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <CacheStorageDataAndJournalSizeMax> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <CacheStorageDataAndJournalSizeMax> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "CacheStorageIndexMax")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.CacheStorageIndexMax = strtoul(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <CacheStorageIndexMax> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <CacheStorageIndexMax> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "Hdcp")
        {
            if (eElement->GetText() != NULL)
                nacp.Hdcp = nacp_tool::set_hdcp(eElement->GetText());
            else
            {
                cerr << "Value of <Hdcp> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "CrashReport")
        {
            if (eElement->GetText() != NULL)
                nacp.CrashReport = nacp_tool::set_crash_report(eElement->GetText());
            else
            {
                cerr << "Value of <CrashReport> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "RuntimeAddOnContentInstall")
        {
            if (eElement->GetText() != NULL)
                nacp.RuntimeAddOnContentInstall = nacp_tool::set_runtime_addoncontent_install(eElement->GetText());
            else
            {
                cerr << "Value of <RuntimeAddOnContentInstall> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "PlayLogQueryableApplicationId")
        {
            if (eElement->GetText() != NULL)
            {
                nacp.PlayLogQueryableApplicationId[0] = strtoull(eElement->GetText(), NULL, 16);
                if (errno == ERANGE)
                {
                    cerr << "Value of <PlayLogQueryableApplicationId> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
                for (int plqaidc = 1; plqaidc < 8; plqaidc++)
                    nacp.PlayLogQueryableApplicationId[plqaidc] = nacp.PlayLogQueryableApplicationId[0];
            }
            else
            {
                cerr << "Value of <PlayLogQueryableApplicationId> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "PlayLogQueryCapability")
        {
            if (eElement->GetText() != NULL)
                nacp.PlayLogQueryCapability = nacp_tool::set_play_log_query_capability(eElement->GetText());
            else
            {
                cerr << "Value of <PlayLogQueryCapability> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "Repair")
        {
            if (eElement->GetText() != NULL)
                nacp.RepairFlag = nacp_tool::set_repair_flag(eElement->GetText());
            else
            {
                cerr << "Value of <Repair> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "Attribute")
        {
            if (eElement->GetText() != NULL)
                nacp.AttributeFlag = nacp_tool::set_attribute_flag(eElement->GetText());
            else
            {
                cerr << "Value of <Attribute> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "ProgramIndex")
        {
            if (eElement->GetText() != NULL)
            {
                try
                {
                    nacp.ProgramIndex = stoi(eElement->GetText(), NULL, 10);
                }
                catch (exception &e)
                {
                    cerr << "Value of <ProgramIndex> element is invalid\n";
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                cerr << "Value of <ProgramIndex> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (strElement == "RequiredNetworkServiceLicenseOnLaunch")
        {
            if (eElement->GetText() != NULL)
                nacp.RequiredNetworkServiceLicenseOnLaunchFlag = nacp_tool::set_required_network_service_license_on_launch(eElement->GetText());
            else
            {
                cerr << "Value of <RequiredNetworkServiceLicenseOnLaunch> element is empty\n";
                exit(EXIT_FAILURE);
            }
        }
        else
            cerr << "Skipping unknown element: " << strElement << "\n";

        eElement = eElement->NextSiblingElement();
    }

    // Convert bitset to uint and set SupportedLanguageFlag
    nacp.SupportedLanguageFlag = slfc_bits.to_ulong();

    // Write NACP
    cout << "Writing " << *output_filepath << "\n";
    ofstream nacp_file(*output_filepath, ofstream::binary | ofstream::out);
    if (nacp_file.fail())
    {
        cerr << "Failed to create " << *output_filepath << "\n";
        exit(EXIT_FAILURE);
    }
    nacp_file.write((char *)&nacp, sizeof(nacp_t));
    nacp_file.close();
    cout << "Created " << *output_filepath << "\n";
}

struct CompareCStrings
{
    bool operator()(const char *lhs, const char *rhs) const
    {
        return std::strcmp(lhs, rhs) < 0;
    }
};

const char *nacp_tool::get_title_lang_name(int lang_id)
{
    map<int, const char *> title_lang_name = {{0, "AmericanEnglish"},
                                              {1, "BritishEnglish"},
                                              {2, "Japanese"},
                                              {3, "French"},
                                              {4, "German"},
                                              {5, "LatinAmericanSpanish"},
                                              {6, "Spanish"},
                                              {7, "Italian"},
                                              {8, "Dutch"},
                                              {9, "CanadianFrench"},
                                              {10, "Portuguese"},
                                              {11, "Russian"},
                                              {12, "Korean"},
                                              {13, "TraditionalChinese"},
                                              {14, "SimplifiedChinese"},
                                              {15, "Unknown_2"}};
    if (title_lang_name.count(lang_id) == 1)
        return title_lang_name[lang_id];
    else
        return "Unknown";
}

int nacp_tool::get_title_lang_id(const char *lang_name)
{
    map<const char *, int, CompareCStrings> title_lang_id = {{"AmericanEnglish", 0},
                                                             {"BritishEnglish", 1},
                                                             {"Japanese", 2},
                                                             {"French", 3},
                                                             {"German", 4},
                                                             {"LatinAmericanSpanish", 5},
                                                             {"Spanish", 6},
                                                             {"Italian", 7},
                                                             {"Dutch", 8},
                                                             {"CanadianFrench", 9},
                                                             {"Portuguese", 10},
                                                             {"Russian", 11},
                                                             {"Korean", 12},
                                                             {"TraditionalChinese", 13},
                                                             {"SimplifiedChinese", 14},
                                                             {"Unknown_2", 15}};
    if (title_lang_id.count(lang_name) == 1)
        return title_lang_id[lang_name];
    else
    {
        cerr << "Value of <Language> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_startup_user_account(uint8_t value)
{
    map<uint8_t, const char *> startup_user_account = {{0, "None"},
                                                       {1, "Required"},
                                                       {2, "RequiredWithNetworkServiceAccountAvailable"}};
    if (startup_user_account.count(value) == 1)
        return startup_user_account[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_startup_user_account(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> startup_user_account = {{"None", 0},
                                                                        {"Required", 1},
                                                                        {"RequiredWithNetworkServiceAccountAvailable", 2}};
    if (startup_user_account.count(value) == 1)
        return startup_user_account[value];
    else
    {
        cerr << "Value of <StartupUserAccount> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_attribute_flag(uint32_t flag)
{
    map<uint32_t, const char *> attribute_flag = {{0, "None"},
                                                  {1, "Demo"},
                                                  {2, "RetailInteractiveDisplay"}};
    if (attribute_flag.count(flag) == 1)
        return attribute_flag[flag];
    else
        return "Unknown";
}

uint32_t nacp_tool::set_attribute_flag(const char *value)
{
    map<const char *, uint32_t, CompareCStrings> attribute_flag = {{"None", 0},
                                                                   {"Demo", 1},
                                                                   {"RetailInteractiveDisplay", 2}};
    if (attribute_flag.count(value) == 1)
        return attribute_flag[value];
    else
    {
        cerr << "Value of <Attribute> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_parental_control_flag(uint32_t flag)
{
    map<uint32_t, const char *> parental_control_flag = {{0, "None"},
                                                         {1, "FreeCommunication"}};
    if (parental_control_flag.count(flag) == 1)
        return parental_control_flag[flag];
    else
        return "Unknown";
}

uint32_t nacp_tool::set_parental_control_flag(const char *flag)
{
    map<const char *, uint32_t, CompareCStrings> parental_control_flag = {{"None", 0},
                                                                          {"FreeCommunication", 1}};
    if (parental_control_flag.count(flag) == 1)
        return parental_control_flag[flag];
    else
    {
        cerr << "Value of <ParentalControl> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_screenshot(uint8_t value)
{
    map<uint8_t, const char *> screenshot = {{0, "Allow"},
                                             {1, "Deny"}};
    if (screenshot.count(value) == 1)
        return screenshot[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_screenshot(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> screenshot = {{"Allow", 0},
                                                              {"Deny", 1}};
    if (screenshot.count(value) == 1)
        return screenshot[value];
    else
    {
        cerr << "Value of <Screenshot> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_videocapture(uint8_t value)
{
    map<uint8_t, const char *> videocapture = {{0, "Disable"},
                                               {1, "Manual"},
                                               {2, "Enable"}};
    if (videocapture.count(value) == 1)
        return videocapture[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_videocapture(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> videocapture = {{"Disable", 0},
                                                                {"Manual", 1},
                                                                {"Enable", 2}};
    if (videocapture.count(value) == 1)
        return videocapture[value];
    else
    {
        cerr << "Value of <VideoCapture> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_dataloss_confirmation(uint8_t value)
{
    map<uint8_t, const char *> dataloss_confirmation = {{0, "None"},
                                                        {1, "Required"}};
    if (dataloss_confirmation.count(value) == 1)
        return dataloss_confirmation[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_dataloss_confirmation(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> dataloss_confirmation = {{"None", 0},
                                                                         {"Required", 1}};
    if (dataloss_confirmation.count(value) == 1)
        return dataloss_confirmation[value];
    else
    {
        cerr << "Value of <DataLossConfirmation> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_play_log_policy(uint8_t value)
{
    map<uint8_t, const char *> play_log_policy = {{0, "All"},
                                                  {1, "LogOnly"},
                                                  {2, "None"}};
    if (play_log_policy.count(value) == 1)
        return play_log_policy[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_play_log_policy(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> play_log_policy = {{"All", 0},
                                                                   {"LogOnly", 1},
                                                                   {"None", 2}};
    if (play_log_policy.count(value) == 1)
        return play_log_policy[value];
    else
    {
        cerr << "Value of <PlayLogPolicy> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_rating_age_organization_name(int org_id)
{
    map<int, const char *> rating_age_organization_name = {{0, "CERO"},
                                                           {1, "GRACGCRB"},
                                                           {2, "GSRMR"},
                                                           {3, "ESRB"},
                                                           {4, "ClassInd"},
                                                           {5, "USK"},
                                                           {6, "PEGI"},
                                                           {7, "PEGIPortugal"},
                                                           {8, "PEGIBBFC"},
                                                           {9, "Russian"},
                                                           {10, "ACB"},
                                                           {11, "OFLC"}};
    if (rating_age_organization_name.count(org_id) == 1)
        return rating_age_organization_name[org_id];
    else
        return "Unknown";
}

int nacp_tool::get_rating_age_organization_id(const char *org_name)
{
    map<const char *, int, CompareCStrings> rating_age_organization_id = {{"CERO", 0},
                                                                          {"GRACGCRB", 1},
                                                                          {"GSRMR", 2},
                                                                          {"ESRB", 3},
                                                                          {"ClassInd", 4},
                                                                          {"USK", 5},
                                                                          {"PEGI", 6},
                                                                          {"PEGIPortugal", 7},
                                                                          {"PEGIBBFC", 8},
                                                                          {"Russian", 9},
                                                                          {"ACB", 10},
                                                                          {"OFLC", 11}};
    if (rating_age_organization_id.count(org_name) == 1)
        return rating_age_organization_id[org_name];
    else
    {
        cerr << "Value of <Organization> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_logo_type(uint8_t value)
{
    map<uint8_t, const char *> logo_type = {{0, "LicensedByNintendo"},
                                            {2, "Nintendo"}};
    if (logo_type.count(value) == 1)
        return logo_type[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_logo_type(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> logo_type = {{"LicensedByNintendo", 0},
                                                             {"Nintendo", 2}};
    if (logo_type.count(value) == 1)
        return logo_type[value];
    else
    {
        cerr << "Value of <LogoType> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_logo_handling(uint8_t value)
{
    map<uint8_t, const char *> logo_handling = {{0, "Auto"},
                                                {1, "Manual"}};
    if (logo_handling.count(value) == 1)
        return logo_handling[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_logo_handling(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> logo_handling = {{"Auto", 0},
                                                                 {"Manual", 1}};
    if (logo_handling.count(value) == 1)
        return logo_handling[value];
    else
    {
        cerr << "Value of <LogoHandling> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_runtime_addoncontent_install(uint8_t value)
{
    map<uint8_t, const char *> runtime_addoncontent_install = {{0, "Deny"},
                                                               {1, "AllowAppend"}};
    if (runtime_addoncontent_install.count(value) == 1)
        return runtime_addoncontent_install[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_runtime_addoncontent_install(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> runtime_addoncontent_install = {{"Deny", 0},
                                                                                {"AllowAppend", 1}};
    if (runtime_addoncontent_install.count(value) == 1)
        return runtime_addoncontent_install[value];
    else
    {
        cerr << "Value of <RuntimeAddOnContentInstall> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_crash_report(uint8_t value)
{
    map<uint8_t, const char *> crash_report = {{0, "Deny"},
                                               {1, "Allow"}};
    if (crash_report.count(value) == 1)
        return crash_report[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_crash_report(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> crash_report = {{"Deny", 0},
                                                                {"Allow", 1}};
    if (crash_report.count(value) == 1)
        return crash_report[value];
    else
    {
        cerr << "Value of <CrashReport> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_hdcp(uint8_t value)
{
    map<uint8_t, const char *> hdcp = {{0, "None"},
                                       {1, "Required"}};
    if (hdcp.count(value) == 1)
        return hdcp[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_hdcp(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> hdcp = {{"None", 0},
                                                        {"Required", 1}};
    if (hdcp.count(value) == 1)
        return hdcp[value];
    else
    {
        cerr << "Value of <Hdcp> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_play_log_query_capability(uint8_t value)
{
    map<uint8_t, const char *> play_log_query_capability = {{0, "None"},
                                                            {1, "WhiteList"},
                                                            {2, "All"}};
    if (play_log_query_capability.count(value) == 1)
        return play_log_query_capability[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_play_log_query_capability(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> play_log_query_capability = {{"None", 0},
                                                                             {"WhiteList", 1},
                                                                             {"All", 2}};
    if (play_log_query_capability.count(value) == 1)
        return play_log_query_capability[value];
    else
    {
        cerr << "Value of <PlayLogQueryCapability> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_repair_flag(uint8_t value)
{
    map<uint8_t, const char *> repair_flag = {{0, "None"},
                                              {1, "SuppressGameCardAccess"}};
    if (repair_flag.count(value) == 1)
        return repair_flag[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_repair_flag(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> repair_flag = {{"None", 0},
                                                               {"SuppressGameCardAccess", 1}};
    if (repair_flag.count(value) == 1)
        return repair_flag[value];
    else
    {
        cerr << "Value of <Repair> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_addoncontent_registration_type(uint8_t value)
{
    map<uint8_t, const char *> addoncontent_registration_type = {{0, "AllOnLaunch"},
                                                                 {1, "OnDemand"}};
    if (addoncontent_registration_type.count(value) == 1)
        return addoncontent_registration_type[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_addoncontent_registration_type(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> addoncontent_registration_type = {{"AllOnLaunch", 0},
                                                                                  {"OnDemand", 1}};
    if (addoncontent_registration_type.count(value) == 1)
        return addoncontent_registration_type[value];
    else
    {
        cerr << "Value of <AddOnContentRegistrationType> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_useraccount_switch_lock(uint8_t value)
{
    map<uint8_t, const char *> useraccount_switch_lock = {{0, "Disable"},
                                                          {1, "Enable"}};
    if (useraccount_switch_lock.count(value) == 1)
        return useraccount_switch_lock[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_useraccount_switch_lock(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> useraccount_switch_lock = {{"Disable", 0},
                                                                           {"Enable", 1}};
    if (useraccount_switch_lock.count(value) == 1)
        return useraccount_switch_lock[value];
    else
    {
        cerr << "Value of <UserAccountSwitchLock> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_required_network_service_license_on_launch(uint8_t value)
{
    map<uint8_t, const char *> required_network_service_license_on_launch = {{0, "None"},
                                                                             {1, "Common"}};
    if (required_network_service_license_on_launch.count(value) == 1)
        return required_network_service_license_on_launch[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_required_network_service_license_on_launch(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> required_network_service_license_on_launch = {{"None", 0},
                                                                                              {"Common", 1}};
    if (required_network_service_license_on_launch.count(value) == 1)
        return required_network_service_license_on_launch[value];
    else
    {
        cerr << "Value of <RequiredNetworkServiceLicenseOnLaunch> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}

const char *nacp_tool::get_startup_user_account_option_flag(uint8_t value)
{
    map<uint8_t, const char *> startup_user_account_option_flag = {{0, "None"},
                                                                   {1, "IsOptional"}};
    if (startup_user_account_option_flag.count(value) == 1)
        return startup_user_account_option_flag[value];
    else
        return "Unknown";
}

uint8_t nacp_tool::set_startup_user_account_option_flag(const char *value)
{
    map<const char *, uint8_t, CompareCStrings> startup_user_account_option_flag = {{"None", 0},
                                                                                    {"IsOptional", 1}};
    if (startup_user_account_option_flag.count(value) == 1)
        return startup_user_account_option_flag[value];
    else
    {
        cerr << "Value of <StartupUserAccountOption> element is invalid\n";
        exit(EXIT_FAILURE);
    }
}
