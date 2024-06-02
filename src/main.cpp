
#include "GameController.h"
#include "const.h"

int main()
{

    try {
        srand(static_cast<unsigned>(time(nullptr)));

        GameController controller;
        controller.execute();

        return EXIT_SUCCESS;
    }

    catch (exception& e) {
        cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...) {
        cerr << "Unknown exception\n";
        return EXIT_FAILURE;
    }

}