
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int
main (int argc, char **argv)
{
  int c;

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"help",     no_argument,       0, 'h'},
          {"version",  no_argument,       0, 'v'},
          {"test",     no_argument,       0, 't'},
          {"run",      required_argument, 0, 'r'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "hvtr:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'h':
          puts ("help option -h\n");
          break;

        case 'v':
          puts ("version option -v\n");
          break;

        case 't':
          printf ("test option `%s'\n");
          break;

        case 'r':
          printf ("Run option  `%s'\n", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    
   }

  exit (0);
}
