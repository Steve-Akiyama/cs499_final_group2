#include "Main.h"


using namespace std;

Main::Main()
{
    // Constructor - no initialization needed
}

void Main::printAsciiTitle() {
    // I promise it doesn't look this weird when you run it
    std::cout << "______ _             _    ______                   " << endl;
    std::cout << "| ___ \\ |           | |   |  ___|                  " << endl;
    std::cout << "| |_/ / | __ _ _ __ | |_  | |_ __ _ _ __ _ __ ___  " << endl;
    std::cout << "|  __/| |/ _` | '_ \\| __| |  _/ _` | '__| '_ ` _ \\ " << endl;
    std::cout << "| |   | | (_| | | | | |_  | || (_| | |  | | | | | |" << endl;
    std::cout << "\\_|   |_|\\__,_|_| |_|\\__| \\_| \\__,_|_|  |_| |_| |_|" << endl;
    std::cout << endl;
    std::cout << " _____ _                 _       _ " << endl;
    std::cout << "/  ___(_)               | |     | |" << endl;
    std::cout << "\\ `--. _ _ __ ___  _   _| | __ _| |_ ___  _ __" << endl;
    std::cout << " `--. \\ | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|" << endl;
    std::cout << "/\\__/ / | | | | | | |_| | | (_| | || (_) | |" << endl;
    std::cout << "\\____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|" << endl;
    return;
}

void Main::start()
{
    printAsciiTitle();

    while (true)
    {
        displayMenu();
        processInput();
    }
}

void Main::displayMenu()
{
    std::cout << "Menu:" << endl;
    std::cout << "1. Run Plant Farm Simulator with manual inputs" << endl;
    std::cout << "2. Auto-Run Plant Farm Simulator with auto-input values: \"2 2\"" << endl;
    std::cout << "3. Run with Value Iteration" << endl;
    std::cout << "4. Run with Actor-Critic" << endl;
    std::cout << "5. Run with Actor-Critic (DEBUG MODE)" << endl;
    std::cout << "6. Exit" << endl;
    std::cout << "Choose an option: ";
}

int Main::askForEpisodeCount()
{
    std::cout << "How many episodes would you like to run? (Integer inputs only!)" << endl;

    string str_choice;
    cin >> str_choice;
    
    // Convert string to integer
    int choice = 0;
    try {
        choice = std::stoi(str_choice);
    } catch (std::invalid_argument& e) {
        std::cout << "Invalid input! Please enter an integer." << endl;
    } catch (std::out_of_range& e) {
        std::cout << "Input out of range! Please enter a smaller number." << endl;
    }

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Print separator
    std::cout << "--------------------" << endl << endl;
    
    return choice;
}


void Main::processInput()
{
    // Take user input
    char *str_choice = new char[1];
    cin >> str_choice;
    int choice = (int)(str_choice[0]) - 48; // Input is converted from string to int so that the program will continue to work even if the user enters a non-number

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Print separator
    std::cout << "--------------------" << endl
         << endl;

    // Handles choice inputs for terminal UI, exit, error handling
    switch (choice)
    {
    case 1:
    {
        TerminalUI terminalUI;
        terminalUI.start();
        break;
    }
    case 2:
    {
        PlantFarm plantfarm;
        int water_input = 2;
        int nitro_input = 2;
        while (!plantfarm.transition(water_input, nitro_input))
        {
            std::cout << "<Water> <Nitrogen> Input: " << water_input << " " << nitro_input << endl; // Format for showing the user what the
            continue;
        }
        break;
    }
    case 3:
    {
        cout << "Running Value Iteration..." << endl;
        ValueIteration valueiter;
        clock_t time_elapsed = valueiter.run(); // Run value iteration
        double time_elapsed_seconds = (double)(time_elapsed) / 1000000;

        if (time_elapsed_seconds < 60.0)
        {
            cout << fixed << setprecision(6)
                 << "Time Elapsed: " << time_elapsed_seconds << " seconds" << endl;
        }
        else if (time_elapsed_seconds < 3600.0)
        {
            time_elapsed_seconds = time_elapsed_seconds - (double)(((int)(time_elapsed_seconds / 60)) * 60);
            int time_elapsed_minutes = (int)(time_elapsed_seconds / 60.0);

            cout << fixed << setprecision(6)
                 << "Time Elapsed: " << time_elapsed_minutes << " minutes, "
                 << time_elapsed_seconds << " seconds" << endl;
        }
        else
        {
            int time_elapsed_hours = (int)(time_elapsed_seconds / 3600.0);
            int time_elapsed_minutes = (int)((int)(time_elapsed_seconds / 60.0) - (time_elapsed_hours * 60));
            time_elapsed_seconds = time_elapsed_seconds - (double)(time_elapsed_minutes * 60);

            cout << fixed << setprecision(6)
                 << "Time Elapsed: " << time_elapsed_hours << " hours, "
                 << time_elapsed_minutes << " minutes, "
                 << time_elapsed_seconds << " seconds" << endl;
        }
        break;
    }
    case 4:
    case 5:
    {
        bool debugMode = (choice == 5); // choice is the variable holding the user's choice
        
        method.setDebug(debugMode); // Sets debug mode on or off depending on selection

        int episodeCount = askForEpisodeCount(); // Asks for episode count

        std::cout << "Running with Actor-Critic with " << episodeCount << " episodes." << endl; // Tells the user what's happening

        method.runActorCritic(episodeCount); //Runs actor-critic

        break;
    }
    case 6:
    {
        std::cout << "Exiting..." << endl
             << endl;
        exit(0);
    }
    default:
    {
        std::cout << "Invalid choice. Please try again." << endl;
        break;
    }
    }
    std::cout << endl << "--------------------" << endl;
}

int main()
{
    Main main;
    main.start();
    return 0;
}
