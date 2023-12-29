// Ecosysteme.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Environnement.h"
#include "Lion.h"
#include "Gazelle.h"
#include "Bananier.h"
#include <chrono>

int main()
{
	Environnement environnement({0,0,0},100);
    environnement.ajouterOrganismesAleatoires(10, 50, 60);

    const int screenWidth = 2400;
    const int screenHeight = 1400;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(165);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Camera3D camera = { 0 };
    camera.position = { 50.0f, 50.0f, 50.0f }; // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type



    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };
        float dt = GetFrameTime();
        environnement.mettreAJour(dt);

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
        environnement.afficher();     

        EndMode3D();

        environnement.afficher2D();
        EndDrawing();

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
	
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
