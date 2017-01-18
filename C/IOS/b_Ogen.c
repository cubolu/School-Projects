/******************************************************************************/
/*b_Ogen.c                                                                    */
/*Riesenie:    IOS-projekt2                                                   */
/*Prelozene:   gcc 4.8.2 (ubuntu 14.04)                                       */
/*Autor:       Jakub Lukac                                                    */
/*Login:       xlukac09                                                       */
/*Rocnik:      1. rocnik BIT                                                  */
/*Datum:       30.04.2015                                                     */
/*e-mail:      xlukac09@stud.fit.vutbr.cz                                     */
/******************************************************************************/

#include "buildh2o.h"

void O_gen(sync_t *shm)
{
   // randomize
   srand(time(NULL) ^ (getpid()<<16));
   pid_t pid_id;
   unsigned long chld_id;
   // N_molecules = N atoms of OXYGEN
   for (unsigned long i = 1; i <= shm->N_molecules; i++) {

      usleep((rand() % (shm->max_O_time + 1)) * 1000);  // time in microsecconds

      pid_id = fork();
      if (pid_id == 0) {      // child code
         // randomize
         srand(time(NULL) ^ (getpid()<<16));

         // process ID starts with 1
         chld_id = i;

         // report status
         fprt_out(OXYGEN, chld_id, "started", shm);

         // add atom to bonding queue
         try_bond_O(chld_id, shm);

         atom_exit(OXYGEN, chld_id, shm);
         // child ended
      }
      else if (pid_id > 0);  // oxygen generator process
      else {
         // TODO kill children
         perror("Error: ");
         exit(2);
      }

   }  // end for

   wait_for_children();
   exit(0);
   // OXYGEN generator ended
}
