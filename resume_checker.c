#include "resume_checker_header.h"
void to_lowercase(char *str) 
{
    for(int i=0;str[i];i++) 
    {
        str[i]=tolower(str[i]);
    }
}

void get_requirements(Requirements *req) 
{
    printf("=== RESUME SCREENING REQUIREMENTS ===\n\n");
    printf("Number of skills to check for: ");
    scanf("%d",&req->num_skills);
    getchar();
    printf("Enter skill requirements (one per line):\n");
    for(int i=0;i<req->num_skills;i++) 
    {
        printf("Skill %d: ",i+1);
        fgets(req->skills[i],MAX_SKILL_LENGTH,stdin);
        req->skills[i][strcspn(req->skills[i],"\n")]=0;
        to_lowercase(req->skills[i]);
    }
    printf("\nAge range requirements:\n");
    printf("Minimum age: ");
    scanf("%d",&req->min_age);
    printf("Maximum age: ");
    scanf("%d",&req->max_age);
    getchar();
    printf("\nMinimum years of experience: ");
    scanf("%d",&req->min_experience);
    getchar();
    printf("\nRequired position/role: ");
    fgets(req->position,MAX_POSITION_LENGTH,stdin);
    req->position[strcspn(req->position,"\n")]=0; 
    to_lowercase(req->position);
    printf("\n=== PROCESSING RESUMES ===\n\n");
}

int extract_number_from_line(const char *line, const char *keyword) 
{
    char *pos=strstr(line,keyword);
    if (pos) 
    {
        pos+=strlen(keyword);
        while(*pos && !isdigit(*pos)) 
        {
            pos++;
        }
        if (*pos) 
        {
            return atoi(pos);
        }
    }
    return -1;
}

int check_file(const char *filename,Requirements *req) 
{
    FILE *file=fopen(filename,"r");
    if(file==NULL) 
    {
        printf("Could not open file: %s\n",filename);
        return 0;
    }
    
    char line[MAX_LINE_LENGTH];
    int skills_found=0;
    int age_match=0;
    int experience_match=0;
    int position_match=0;
    int skill_found[MAX_SKILLS]={0};
    
    while(fgets(line,sizeof(line),file)) 
    {
        char line_lower[MAX_LINE_LENGTH];
        strcpy(line_lower, line);
        to_lowercase(line_lower);
        for (int i=0;i<req->num_skills;i++) 
        {
            if(!skill_found[i] && strstr(line_lower, req->skills[i])) 
            {
                skills_found++;
                skill_found[i] = 1;
            }
        }
        int age = extract_number_from_line(line_lower, "age");
        if(age==-1) 
            age=extract_number_from_line(line_lower,"years old");
        if(age!=-1 && age>=req->min_age && age<=req->max_age) 
        {
            age_match=1;
        }
        int experience=extract_number_from_line(line_lower,"experience");
        if(experience==-1) 
            experience=extract_number_from_line(line_lower,"years");
        if(experience!=-1 && experience>=req->min_experience) 
        {
            experience_match=1;
        }
        if(strstr(line_lower,req->position)) 
        {
            position_match=1;
        }
    }
    fclose(file);
    if(skills_found>=req->num_skills && age_match && experience_match && position_match) 
    {
        return 1;
    }
    return 0;
}

void print_file_contents(const char *filename) 
{
    FILE *file=fopen(filename,"r");
    if(file==NULL) 
    {
        printf("Could not open file: %s\n",filename);
        return;
    }
    printf("\n============================================================\n");
    printf("RESUME CONTENT: %s\n",filename);
    printf("============================================================\n");
    char line[MAX_LINE_LENGTH];
    while(fgets(line, sizeof(line),file)) 
    {
        printf("%s",line);
    }   
    printf("\n============================================================\n\n");
    fclose(file);
}

void process_resumes(void) 
{
    const char *files[TOTAL_FILES]=
    {
        "C:/Users/nandu/Desktop/resumes/resume1.txt",
        "C:/Users/nandu/Desktop/resumes/resume2.txt",
        "C:/Users/nandu/Desktop/resumes/resume3.txt",
        "C:/Users/nandu/Desktop/resumes/resume4.txt",
        "C:/Users/nandu/Desktop/resumes/resume5.txt"
    };
    
    Requirements req;
    get_requirements(&req);
    
    printf("MATCHING RESUMES:\n");
    printf("--------------------\n");
    
    int matches_found=0;
    
    for(int i=0;i<TOTAL_FILES;i++) 
    {
        if(check_file(files[i],&req)) 
        {
            matches_found++;
            printf("\nMATCH %d: %s\n",matches_found,files[i]);
            print_file_contents(files[i]);
        }
    }
    
    if(matches_found==0) 
    {
        printf("\nNo resumes match the specified criteria.\n");
    } 
    else 
    {
        printf("\nTotal matching resumes: %d out of %d\n",matches_found,TOTAL_FILES);
    }
}

int main() 
{
    printf("RESUME SCREENING SYSTEM\n");
    printf("==================================================\n\n");
    
    process_resumes();
    
    printf("\nScreening completed successfully!\n");
    return 0;
}