
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

bool quit(string com)
{
    string up="QUIT";
    string low="quit";
    if(com=="Q"||(com=="q")||(com=="0"))
    {
        return true;
    }
    else if(com.size()!=4)
    {
        return false;
    }
    else
    {
        for(int i=0;i<com.size();i++)
        {
            if((com.substr(i,1)!=up.substr(i,1))&&(com.substr(i,1)!=low.substr(i,1)))
            {
                return false;
            }
        }
        return true;
    }
}

void sendEmail(string addr, string subject, string content, string attachment){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    string cmd;
    cmd = "echo " + content + " | mailx -s " + subject + " ";
    if (attachment == "")
        cmd += addr;
    else {
        attachment = "\"" + attachment + "\"";
        cmd += "-a "  + attachment + " " + addr;
    }
    cout << "|" << cmd << "|" << endl;
    system(cmd.c_str());
}

