#include<stdio.h>
struct Core{
	
	int extraversion,introversion,sensing,intuition,thinking,feeling,judging,perceiving;
};

    char *ques[51]={
    "You regularly make new friends?",
    "You feel comfortable just walking up to someone you find interesting and striking up a conversation?",
    "You usually prefer to be around others rather than on your own?",
    "You enjoy participating in team-based activities?",
    "You can easily connect with people you have just met?",
    "Your friends would describe you as lively and outgoing?",
    "You feel more drawn to busy, bustling atmospheres than to quiet, intimate places?",
    

    "You find the idea of networking or promoting yourself to strangers very daunting?",
    "You rarely worry about whether you make a good impression on people you meet?",
    "You enjoy solitary hobbies or activities more than group ones?",
    "You usually wait for others to introduce themselves first at social gatherings?",
    "You avoid making phone calls?",
    

    "You enjoy exploring unfamiliar ideas and viewpoints?",
    "You are drawn to various forms of creative expression, such as writing?",
    "Complex and novel ideas excite you more than simple and straightforward ones?",
    "You enjoy experimenting with new and untested approaches?",
    "You prefer tasks that require you to come up with creative solutions rather than follow concrete steps?",
    "You actively seek out new experiences and knowledge areas to explore?",
    
    
    "You are not too interested in discussions about various interpretations of creative works?",
    "You become bored or lose interest when the discussion gets highly theoretical?",
    "You like to use organizing tools like schedules and lists?",
    "You struggle with deadlines?",
    "You are not too interested in discussing theories on what the world could look like in the future?",
    
    
    "When facts and feelings conflict, you usually find yourself following your heart?",
    "You often feel overwhelmed?",
    "Your mood can change very quickly?",
    "You prioritize facts over peoples feelings when determining a course of action?",
    "Peoples stories and emotions speak louder to you than numbers or data?",
    "Your emotions control you more than you control them?",
    "You prioritize proving your point over preserving the feelings of others?",
    "When making decisions, you focus more on how the affected people might feel than on what is most logical or efficient?",
    "In disagreements, you prioritize being sensitive over being completely honest?",
    "You rarely second-guess the choices that you have made?",
    "Your living and working spaces are clean and organized?",
    
    
    "You are still bothered by mistakes that you made a long time ago?",
    "You usually base your choices on objective facts rather than emotional impressions?",
    "You are not easily swayed by emotional arguments?",
    "You favor efficiency in decisions, even if it means disregarding some emotional aspects?",
    "You enjoy debating ethical dilemmas?",
    "If a decision feels right to you, you often act on it without needing further proof?",
    "When someone thinks highly of you, you wonder how long it will take them to feel disappointed in you?",
    
    
    "You prioritize and plan tasks effectively, often completing them well before the deadline?",
    "You are prone to worrying that things will take a turn for the worse?",
    "You prefer to do your chores before allowing yourself to relax?",
    "You like to have a to-do list for each day?",
    "Your personal work style is closer to spontaneous bursts of energy than organized and consistent efforts?",
    "You complete things methodically without skipping over any steps?",
    
    
    "You struggle with deadlines?",
    "You rarely feel insecure?",
    "You find it challenging to maintain a consistent work or study schedule?",
    "If your plans are interrupted, your top priority is to get back on track as soon as possible?"
    };
void askQue(int n,struct Core *c)
{
    int points;
    printf("%d. %s\n",n+1,ques[n]);
    printf("Answer on a scale of 1-5 (1 - Strongly Disagree, 5 - Strongly Agree): ");
    do{
        scanf("%d",&points);
        if(points<1 || points>5)
        printf("Invalid input. Please enter a number between 1 and 5.\n");
        }while(points<1 || points>5);

    if(points>=4)
    {
        if(n<7)
        c->extraversion++;
        else if(n<12)
        c->introversion++;
        else if (n<18)
        c->intuition++;
        else if (n<23)
        c->sensing++;
        else if (n<34)
        c->feeling++;
        else if (n<41)
        c->thinking++;
        else if (n<48)
        c->judging++;
        else
        c->perceiving++;
    }
    else if(points<=2)
    {
        if(n<7)
        c->introversion++;
        else if(n<12)
        c->extraversion++;
        else if (n<18)
        c->sensing++;
        else if (n<23)
        c->intuition++;
        else if (n<34)
        c->thinking++;
        else if (n<41)
        c->feeling++;
        else if (n<48)
        c->perceiving++;
        else
        c->judging++;
    }
    else
    {
        if(n<12)
        {
            c->extraversion++;
            c->introversion++;
        }
        else if(n<23)
        {
            c->sensing++;
            c->intuition++;
        }
        else if(n<41)
        {
            c->thinking++;
            c->feeling++;
        }
        else
        {
            c->perceiving++;
            c->judging++;
        }
    }

}
int main()
{
    struct Core c={0};
    printf("Welcome to the Personality Career Test!\n\n");
    for(int i=0;i<51;i++)
    {
        askQue(i,&c);
    }
    printf("\nYour Personality Results:\n");
    printf("Extraversion: %d, Introversion: %d\n",c.extraversion,c.introversion);
    printf("Sensing: %d, Intuition: %d\n",c.sensing,c.intuition);
    printf("Thinking: %d, Feeling: %d\n",c.thinking,c.feeling);
    printf("Judging: %d, Perceiving: %d\n",c.judging,c.perceiving);
    printf("\nCareer Suggestions:\n");
    if(c.extraversion>c.introversion)
    {
        printf("the most suiitable career for you would be carrer related to Education and training,Marketing,Politics and Journalism.\n");
    }
    else if(c.extraversion<c.introversion)
    {
        printf("You may excel in  more solitary research-based careers like Writer, Analyst,Skilled trader or Scientist.\n");
    }
    else
    {
        printf("You have a balanced preference for both social and isolated environments, so careers like Project Management, Consulting, or Entrepreneurship might suit you.\n");
    }
    if(c.sensing>c.intuition)
    {
        printf("You might be suited to practical careers such as Engineering, Accounting, or Healthcare.\n");
    }
    else if(c.sensing<c.intuition)
    {
        printf("You may thrive in creative or theoretical fields like Design, Psychology, or Innovation.\n");
    }
    else
    {
        printf("You have a balanced approach to both practical and creative tasks, making you well-suited for careers in Research, Urban Planning, or Product Management.\n");
    }
    if(c.thinking>c.feeling)
    {
        printf("you may consider analytical careers like Law, IT, or Data Analysis.\n");
    }
    else if(c.thinking<c.feeling)
    {
        printf("you are more likely to enjoy  careers which are focused on empathy, such as Counseling, HR, or Social Work.\n");
    }
    else
    {
        printf("You have a very strong approach to decision-making, which may make you excel in roles such as Mediator, Consultant, or Executive Leadership.\n");
    }
    if(c.judging>c.perceiving)
    {
        printf("You will be good at structured careers like Project Management, Business, or Law.\n");
    }
    else if(c.judging<c.perceiving)
    {
        printf("You may excel in flexible careers like Entrepreneurship, Consulting, or the Arts.\n");
    }
    else
    {
        printf("You have a flexible and organized approach, making you ideal for roles in Operations, Event Planning, or Freelancing.\n");
    }
    return 0;
}
