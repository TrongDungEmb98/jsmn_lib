#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

static const char *JSON_STRING =
    "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
    "\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

int main() {
  static int r;
  static jsmn_parser p;
  static jsmntok_t t[128]; /* We expect no more than 128 tokens */

  r = json_parser(JSON_STRING, &p, t, sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  int pos_user = get_pos_key(JSON_STRING, t, r, "user");
  if (pos_user == -1) {
    printf("Key \"user\" not found\n");
    return 1;
  }

  int inter = json_get_int(JSON_STRING, t, r, "uid");
  printf("%d\n", inter);

  char buf[32];
  int len = json_get_str(JSON_STRING, t, r, "user", buf);
  printf("%s\n", buf);

  memset(buf, 0, 32);
  json_get_arr_obj(JSON_STRING, t, r, "groups", 0, buf);
  printf("%s\n", buf);

  //   /* Loop over all keys of the root object */
  //   for (i = 1; i < r; i++) {
  //     if (jsoneq(JSON_STRING, &t[i], "user") == 0) {
  //       /* We may use strndup() to fetch string value */
  //       printf("- User: %.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING +
  //       t[i + 1].start); i++;
  //     } else if (jsoneq(JSON_STRING, &t[i], "admin") == 0) {
  //       /* We may additionally check if the value is either "true" or "false"
  //       */ printf("- Admin: %.*s\n", t[i + 1].end - t[i + 1].start,
  //       JSON_STRING + t[i + 1].start); i++;
  //     } else if (jsoneq(JSON_STRING, &t[i], "uid") == 0) {
  //       /* We may want to do strtol() here to get numeric value */
  //       printf("- UID: %.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING +
  //       t[i + 1].start); i++;
  //     } else if (jsoneq(JSON_STRING, &t[i], "groups") == 0) {
  //       int j;
  //       printf("- Groups:\n");
  //       if (t[i + 1].type != JSMN_ARRAY) {
  //         continue; /* We expect groups to be an array of strings */
  //       }
  //       for (j = 0; j < t[i + 1].size; j++) {
  //         jsmntok_t *g = &t[i + j + 2];
  //         printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
  //       }
  //       i += t[i + 1].size + 1;
  //     } else {
  //       printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
  //              JSON_STRING + t[i].start);
  //     }
  //   }
  return EXIT_SUCCESS;
}
