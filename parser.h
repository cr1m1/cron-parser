#include <vector>
#include <set>
#include <string>
#include <sstream>

enum TimeType
{
    MINUTE,
    HOUR,
    DAY_OF_MONTH,
    MONTH,
    DAY_OF_WEEK
};

class Parser
{
public:
    // output data
    std::set<int> minutes;
    std::set<int> hours;
    std::set<int> daysOfMonth;
    std::set<int> monthes;
    std::set<int> daysOfWeek;
    std::string cmd;

    Parser(
        std::string min,
        std::string hour,
        std::string dom,
        std::string mon,
        std::string dow,
        std::string command)
    {
        parseMin(min);
        parseHour(hour);
        parseDayOfMonth(dom);
        parseMonth(mon);
        parseDayOfWeek(dow);
        cmd = command;
    }

    void print()
    {
        printf(
            "minute %s\nhour %s\nday of month %s\nmonth %s\nday of week %s\ncommand %s",
            join(minutes).c_str(),
            join(hours).c_str(),
            join(daysOfMonth).c_str(),
            join(monthes).c_str(),
            join(daysOfWeek).c_str(),
            cmd.c_str());
    }

    std::string getOutput()
    {
        return join(minutes) + "\n" + join(hours) + "\n" + join(daysOfMonth) + "\n" + join(monthes) + "\n" + join(daysOfWeek) + "\n" + cmd + "\n";
    }

private:
    void parseMin(std::string m)
    {
        minutes = parse(m, MINUTE);
    }

    void parseHour(std::string h)
    {
        hours = parse(h, HOUR);
    }

    void parseDayOfMonth(std::string dom)
    {
        daysOfMonth = parse(dom, DAY_OF_MONTH);
    }

    void parseMonth(std::string m)
    {
        monthes = parse(m, MONTH);
    }

    void parseDayOfWeek(std::string dow)
    {
        daysOfWeek = parse(dow, DAY_OF_WEEK);
    }

    std::set<int> parse(std::string s, TimeType t)
    {
        std::set<int> result;
        int startPoint;
        int endPoint;

        switch (t)
        {
        case MINUTE:
            startPoint = 0;
            endPoint = 59;
            break;
        case HOUR:
            startPoint = 0;
            endPoint = 23;
            break;
        case DAY_OF_MONTH:
            startPoint = 1;
            endPoint = 31;
            break;
        case MONTH:
            startPoint = 1;
            endPoint = 12;
            break;
        case DAY_OF_WEEK:
            startPoint = 1;
            endPoint = 7;
            break;
        }

        if (s == "*")
        {
            for (int i = startPoint; i <= endPoint; i++)
            {
                result.insert(i);
            }
            return result;
        }

        std::vector<std::string> arr;
        if (s.find(",") != -1)
        {
            arr = split(s, ",");
        }
        else
        {
            arr.push_back(s);
        }

        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i].find("-") != -1)
            {
                try
                {
                    int first = std::stoi(arr[i].substr(0, arr[i].find("-")));
                    int second = std::stoi(arr[i].substr(arr[i].find("-") + 1));
                    if (second < first || first < startPoint || second > endPoint)
                    {
                        throw("incorrect input. example: 0-15.\n");
                    }
                    for (int i = first; i <= second; i++)
                    {
                        result.insert(i);
                    }
                    continue;
                }
                catch (const char *err)
                {
                    printf("error: %s", err);
                    exit(0);
                }
            }
            if (arr[i].find("/") != -1)
            {
                try
                {
                    int first = (arr[i].substr(0, arr[i].find("/")) == "*") ? startPoint : std::stoi(arr[i].substr(0, arr[i].find("/")));
                    int second = std::stoi(arr[i].substr(arr[i].find("/") + 1));
                    if (first < startPoint || second > endPoint)
                    {
                        throw("incorrect input. example: */15 or 30/2.\n");
                    }
                    for (int i = first; i <= endPoint; i += second)
                    {
                        result.insert(i);
                    }
                    continue;
                }
                catch (const char *err)
                {
                    printf("error: %s", err);
                    exit(0);
                }
            }
            result.insert(std::stoi(arr[i]));
        }
        return result;
    }

    // a function to concatenate vector arrays into string
    std::string join(std::set<int> &s)
    {
        std::stringstream ss;
        int i = 0;
        for (auto e : s)
        {
            if (i != 0)
            {
                ss << " ";
            }
            ss << e;
            i++;
        }
        return ss.str();
    }

    std::vector<std::string> split(std::string s, std::string delimeter)
    {
        std::vector<std::string> res;
        size_t start = 0;
        size_t end;
        size_t dell = delimeter.length(); // length of delimeter
        std::string token;

        while ((end = s.find(delimeter, start)) != -1)
        {
            token = s.substr(start, end - start);
            start = end + dell;
            res.push_back(token);
        }
        res.push_back(s.substr(start));
        return res;
    }
};