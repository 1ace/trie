import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--prefix')
parser.add_argument('--entrypoints')
parser.add_argument('--header')
args = parser.parse_args()

entrypoints = None
with open(args.entrypoints) as ep:
    entrypoints = [line.strip() for line in ep.readlines()]

with open(args.header, 'w') as header:
    header.write('''
        #include <stdbool.h>
        #include <stdlib.h>
        #include <string.h>

        #define __ARRAY_SIZE(a) (sizeof(a) / sizeof(a)[0])

        struct __''' + args.prefix + '''_entrypoint {
            char *name;
            void *ptr;
        };

        static const struct __''' + args.prefix + '''_entrypoint
        __''' + args.prefix + '''_entrypoints[] = {
        ''' + ','.join([
            '{ .name = "' + entrypoint + '", .ptr = ' + entrypoint + ' }'
            for entrypoint in entrypoints
        ]) + '''
        };

        static int
        __''' + args.prefix + '''_compare(const void *key, const void *elem)
        {
            const char *name = key;
            const struct __''' + args.prefix + '''_entrypoint * entrypoint = elem;
            return strcmp(name, entrypoint->name);
        }

        static bool
        ''' + args.prefix + '''_fetch(char const * const name, void const * * const value)
        {
            if (!name || !name[0])
                return false;

            const struct __''' + args.prefix + '''_entrypoint * entrypoint =
                bsearch(name,
                __''' + args.prefix + '''_entrypoints,
                __ARRAY_SIZE(__''' + args.prefix + '''_entrypoints),
                sizeof(__''' + args.prefix + '''_entrypoints[0]),
                __''' + args.prefix + '''_compare);

            if (entrypoint)
            {
                if (value)
                    *value = entrypoint->ptr;
                return true;
            }

            return false;
        }
    ''')
