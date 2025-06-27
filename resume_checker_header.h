#ifndef RESUME_CHECKER_H
#define RESUME_CHECKER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TOTAL_FILES 5
#define MAX_LINE_LENGTH 1000
#define MAX_SKILLS 100
#define MAX_SKILL_LENGTH 100
#define MAX_POSITION_LENGTH 100

typedef struct 
{
    char skills[MAX_SKILLS][MAX_SKILL_LENGTH];
    int num_skills;
    int min_age;
    int max_age;
    int min_experience;
    char position[MAX_POSITION_LENGTH];
}Requirements;

void to_lowercase(char *str);
void get_requirements(Requirements *req);
int extract_number_from_line(const char *line, const char *keyword);
int check_file(const char *filename, Requirements *req);
void print_file_contents(const char *filename);
void process_resumes(void);

#endif