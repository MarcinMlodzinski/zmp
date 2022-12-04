#define ROTATE_SPEED     30
/*
 *  Przykładowy zestaw poleceń
 */
  BEGIN_PARALLEL_ACTIONS
  Set   Podstawa 2 0 30    // Polozenie obiektu A 
  Set   Podstawa.Ramie1 10 10 0   // Polozenie obiektu B
  END_PARALLEL_ACTIONS
  BEGIN_PARALLEL_ACTIONS
  Rotate Podstawa ROTATE_SPEED 40
  END_PARALLEL_ACTIONS
  BEGIN_PARALLEL_ACTIONS
  Pause 1000 /* Zawieszenie na 1 sek. */
  END_PARALLEL_ACTIONS
  BEGIN_PARALLEL_ACTIONS
  Move  Podstawa.Ramie1.Ramie2  10 10
  END_PARALLEL_ACTIONS
  BEGIN_PARALLEL_ACTIONS
  Rotate Podstawa ROTATE_SPEED 60 /* Rotate i Move wykonywane razem */
  Move  Podstawa 10 20            /* powoduja jazde po luku         */
  END_PARALLEL_ACTIONS
