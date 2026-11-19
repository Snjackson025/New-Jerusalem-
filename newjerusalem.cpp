#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace NewJerusalem {

constexpr const char* VERSION = "1.0.0";
constexpr const char* DIRECTIVE =
    "Pursue truth, preserve knowledge, encourage wisdom, and serve humanity without harm.";

std::string Timestamp() {
    std::time_t now = std::time(nullptr);
    std::tm timeInfo{};

#ifdef _WIN32
    localtime_s(&timeInfo, &now);
#else
    localtime_r(&now, &timeInfo);
#endif

    std::ostringstream output;
    output << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
    return output.str();
}

std::string Lower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

std::string ReadLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void Pause() {
    std::cout << "\nPress ENTER to continue...";
    std::string ignored;
    std::getline(std::cin, ignored);
}

class EventLogger {
private:
    std::string filename = "newjerusalem_events.txt";

public:
    void Log(const std::string& event) {
        std::ofstream file(filename, std::ios::app);
        if (file) {
            file << "[" << Timestamp() << "] " << event << '\n';
        }
    }
};

struct KnowledgeRecord {
    int id = 0;
    std::string category;
    std::string title;
    std::string content;
    std::string timestamp;
};

struct TimelineEvent {
    int id = 0;
    std::string title;
    std::string description;
    std::string date;
};

class KnowledgeEngine {
private:
    std::vector<KnowledgeRecord> records;
    int nextId = 1;
    const std::string filename = "newjerusalem_knowledge.txt";

public:
    KnowledgeEngine() {
        Load();
    }

    void AddRecord() {
        KnowledgeRecord record;

        record.id = nextId++;
        record.category = ReadLine("Category: ");
        record.title = ReadLine("Title: ");
        record.content = ReadLine("Knowledge or observation: ");
        record.timestamp = Timestamp();

        records.push_back(record);
        Save();

        std::cout << "\nKnowledge record saved. ID: "
                  << record.id << '\n';
    }

    void DisplayAll() const {
        if (records.empty()) {
            std::cout << "\nNo knowledge records available.\n";
            return;
        }

        for (const auto& record : records) {
            DisplayRecord(record);
        }
    }

    void DisplayRecord(const KnowledgeRecord& record) const {
        std::cout << "\n----------------------------------\n";
        std::cout << "ID: " << record.id << '\n';
        std::cout << "Category: " << record.category << '\n';
        std::cout << "Title: " << record.title << '\n';
        std::cout << "Date: " << record.timestamp << '\n';
        std::cout << "Content:\n" << record.content << '\n';
    }

    void Search() const {
        std::string query = Lower(ReadLine("Search knowledge: "));
        bool found = false;

        for (const auto& record : records) {
            std::string searchable =
                Lower(record.category + " " +
                      record.title + " " + record.content);

            if (searchable.find(query) != std::string::npos) {
                DisplayRecord(record);
                found = true;
            }
        }

        if (!found) {
            std::cout << "\nNo matching records found.\n";
        }
    }

    void ShowCategories() const {
        std::map<std::string, int> categories;

        for (const auto& record : records) {
            categories[record.category]++;
        }

        std::cout << "\nKNOWLEDGE CATEGORIES\n";

        if (categories.empty()) {
            std::cout << "No categories recorded.\n";
            return;
        }

        for (const auto& item : categories) {
            std::cout << item.first << ": "
                      << item.second << " records\n";
        }
    }

    void Save() const {
        std::ofstream file(filename);

        if (!file) {
            std::cout << "Unable to save knowledge database.\n";
            return;
        }

        file << nextId << '\n';

        for (const auto& record : records) {
            file << record.id << '\n'
                 << std::quoted(record.category) << '\n'
                 << std::quoted(record.title) << '\n'
                 << std::quoted(record.content) << '\n'
                 << std::quoted(record.timestamp) << '\n';
        }
    }

    void Load() {
        std::ifstream file(filename);

        if (!file) {
            return;
        }

        file >> nextId;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        KnowledgeRecord record;

        while (file >> record.id) {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(record.category))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(record.title))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(record.content))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(record.timestamp))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            records.push_back(record);
        }
    }

    std::size_t Count() const {
        return records.size();
    }
};

class InquiryEngine {
public:
    void BeginInquiry() {
        std::cout << "\n========== INQUIRY ==========\n";

        std::string question = ReadLine("What question are we examining? ");
        std::string known = ReadLine("What is currently known? ");
        std::string unknown = ReadLine("What remains unknown? ");
        std::string evidence = ReadLine("What evidence is available? ");

        std::cout << "\nINQUIRY REPORT\n";
        std::cout << "Question: " << question << '\n';
        std::cout << "Known: " << known << '\n';
        std::cout << "Unknown: " << unknown << '\n';
        std::cout << "Evidence: " << evidence << '\n';

        std::cout << "\nNext step: identify what evidence would "
                     "help resolve the unknown.\n";
    }
};

class ReasoningEngine {
public:
    void ExamineClaim() {
        std::cout << "\n========== REASONING ==========\n";

        std::string claim = ReadLine("Enter a claim: ");
        std::string evidence = ReadLine("Enter supporting evidence: ");
        std::string alternative = ReadLine("Enter an alternative explanation: ");

        std::cout << "\nREASONING REVIEW\n";
        std::cout << "Claim: " << claim << '\n';
        std::cout << "Evidence: " << evidence << '\n';
        std::cout << "Alternative explanation: " << alternative << '\n';

        std::cout << "\nReview questions:\n";
        std::cout << "1. Does the evidence directly support the claim?\n";
        std::cout << "2. Can the evidence be independently verified?\n";
        std::cout << "3. Have competing explanations been considered?\n";
        std::cout << "4. What information could disprove the claim?\n";
        std::cout << "5. What conclusion is justified by the evidence?\n";
    }
};

class ReflectionEngine {
public:
    void Reflect() {
        std::cout << "\n========== REFLECTION ==========\n";

        std::string observation = ReadLine("What did you observe? ");
        std::string interpretation = ReadLine("What did you interpret? ");
        std::string assumption = ReadLine("What assumption might be involved? ");
        std::string lesson = ReadLine("What did you learn? ");

        std::cout << "\nREFLECTION SUMMARY\n";
        std::cout << "Observation: " << observation << '\n';
        std::cout << "Interpretation: " << interpretation << '\n';
        std::cout << "Assumption: " << assumption << '\n';
        std::cout << "Lesson: " << lesson << '\n';

        std::cout << "\nReflection complete.\n";
    }
};

class ChronologyEngine {
private:
    std::vector<TimelineEvent> events;
    int nextId = 1;
    const std::string filename = "newjerusalem_timeline.txt";

public:
    ChronologyEngine() {
        Load();
    }

    void AddEvent() {
        TimelineEvent event;

        event.id = nextId++;
        event.date = ReadLine("Event date or time: ");
        event.title = ReadLine("Event title: ");
        event.description = ReadLine("Event description: ");

        events.push_back(event);
        Save();

        std::cout << "\nTimeline event saved.\n";
    }

    void Display() const {
        std::cout << "\n========== CHRONOLOGY ==========\n";

        if (events.empty()) {
            std::cout << "No timeline events recorded.\n";
            return;
        }

        for (const auto& event : events) {
            std::cout << "\nID: " << event.id
                      << "\nDate: " << event.date
                      << "\nTitle: " << event.title
                      << "\nDescription: " << event.description
                      << "\n";
        }
    }

    void Save() const {
        std::ofstream file(filename);

        if (!file) {
            std::cout << "Unable to save timeline.\n";
            return;
        }

        file << nextId << '\n';

        for (const auto& event : events) {
            file << event.id << '\n'
                 << std::quoted(event.date) << '\n'
                 << std::quoted(event.title) << '\n'
                 << std::quoted(event.description) << '\n';
        }
    }

    void Load() {
        std::ifstream file(filename);

        if (!file) return;

        file >> nextId;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        TimelineEvent event;

        while (file >> event.id) {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(event.date))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(event.title))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(file >> std::quoted(event.description))) break;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            events.push_back(event);
        }
    }
};

class KnowledgeCharacter {
public:
    void Respond() {
        std::string input = ReadLine("\nNew Jerusalem AI: ");

        std::string message = Lower(input);

        std::cout << "\nNew Jerusalem AI: ";

        if (message.find("truth") != std::string::npos) {
            std::cout << "Truth requires examination, evidence, "
                         "and a willingness to revise conclusions.\n";
        }
        else if (message.find("knowledge") != std::string::npos) {
            std::cout << "Knowledge grows when information is examined, "
                         "organized, tested, and shared responsibly.\n";
        }
        else if (message.find("question") != std::string::npos) {
            std::cout << "A meaningful question can reveal what is known "
                         "and expose what remains unknown.\n";
        }
        else if (message.find("time") != std::string::npos) {
            std::cout << "Time can be examined through events, sequences, "
                         "measurements, and recorded observations.\n";
        }
        else if (message.find("help") != std::string::npos) {
            std::cout << "I can help organize knowledge, examine claims, "
                         "record events, and support reflection.\n";
        }
        else {
            std::cout << "Let's examine that carefully. What do we know, "
                         "what remains uncertain, and what evidence "
                         "could help us understand it?\n";
        }
    }
};

class NewJerusalemAI {
private:
    KnowledgeEngine knowledge;
    InquiryEngine inquiry;
    ReasoningEngine reasoning;
    ReflectionEngine reflection;
    ChronologyEngine chronology;
    KnowledgeCharacter character;
    EventLogger logger;

public:
    void Run() {
        logger.Log("New Jerusalem AI started.");

        bool running = true;

        while (running) {
            DisplayMenu();

            std::string choice = ReadLine("\nSelect an option: ");

            if (choice == "1") {
                knowledge.AddRecord();
                logger.Log("Knowledge record created.");
            }
            else if (choice == "2") {
                knowledge.DisplayAll();
            }
            else if (choice == "3") {
                knowledge.Search();
            }
            else if (choice == "4") {
                knowledge.ShowCategories();
            }
            else if (choice == "5") {
                inquiry.BeginInquiry();
                logger.Log("Inquiry completed.");
            }
            else if (choice == "6") {
                reasoning.ExamineClaim();
                logger.Log("Claim examination completed.");
            }
            else if (choice == "7") {
                reflection.Reflect();
                logger.Log("Reflection completed.");
            }
            else if (choice == "8") {
                chronology.AddEvent();
                logger.Log("Timeline event created.");
            }
            else if (choice == "9") {
                chronology.Display();
            }
            else if (choice == "10") {
                character.Respond();
            }
            else if (choice == "11") {
                DisplayStatus();
            }
            else if (choice == "0") {
                running = false;
                logger.Log("New Jerusalem AI stopped.");
            }
            else {
                std::cout << "\nInvalid selection.\n";
            }

            if (running) Pause();
        }

        std::cout << "\nNew Jerusalem AI shutting down.\n";
    }

private:
    void DisplayMenu() const {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "          NEW JERUSALEM AI\n";
        std::cout << "========================================\n";
        std::cout << "Version: " << VERSION << '\n';
        std::cout << DIRECTIVE << "\n\n";

        std::cout << "1. Add Knowledge\n";
        std::cout << "2. View Knowledge\n";
        std::cout << "3. Search Knowledge\n";
        std::cout << "4. Knowledge Categories\n";
        std::cout << "5. Begin Inquiry\n";
        std::cout << "6. Examine a Claim\n";
        std::cout << "7. Reflection Session\n";
        std::cout << "8. Record Timeline Event\n";
        std::cout << "9. View Chronology\n";
        std::cout << "10. Speak with AI Character\n";
        std::cout << "11. System Status\n";
        std::cout << "0. Exit\n";
        std::cout << "========================================\n";
    }

    void DisplayStatus() const {
        std::cout << "\n========== SYSTEM STATUS ==========\n";
        std::cout << "System: New Jerusalem AI\n";
        std::cout << "Version: " << VERSION << '\n';
        std::cout << "Knowledge records: " << knowledge.Count() << '\n';
        std::cout << "Storage: Local file system\n";
        std::cout << "Knowledge engine: Active\n";
        std::cout << "Inquiry engine: Active\n";
        std::cout << "Reasoning engine: Active\n";
        std::cout << "Reflection engine: Active\n";
        std::cout << "Chronology engine: Active\n";
        std::cout << "Character interface: Active\n";
    }
};

} // namespace NewJerusalem

int main() {
    NewJerusalem::NewJerusalemAI system;
    system.Run();
    return 0;
}
