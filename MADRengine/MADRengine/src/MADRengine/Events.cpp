#include "Events.h"
#include "Tuple"



Event::Event(string t, int p)
    : name(t), priority(p)
{
}


Event::Event(string t, int p, std::any d, bool ignorePause)
    : name(t), priority(p), data(d), IgnorePause(ignorePause) {}


string Event::GetName() const
{
    return name;
}

void Event::Send()
{
    EventSender::GetInstance().SendEventImmediately(*this);
}


// For the tuple
constexpr int FUNCTION = 0;
constexpr int CLEAR = 1;

void EventSender::AddListener(const string& name, EventFunction eventFunc, bool clearAutomatic)
{
    string n = name;

    // to lower case
    transform(n.begin(), n.end(), n.begin(), ::tolower);

    allListeners[n].push_back(std::tuple<EventFunction, bool>(eventFunc, clearAutomatic));
}

void EventSender::RemoveListener(const string& name)
{
    string n = name;
    // to lower case
    transform(n.begin(), n.end(), n.begin(), ::tolower);

    std::map< string, std::vector<std::tuple<EventFunction, bool>> >::iterator itr = allListeners.find(n);
    if (itr != allListeners.end())
    {
        allListeners.erase(itr);
    }
}

void EventSender::AutomaticRemoveListeners()
{
    std::map< string, std::vector<std::tuple<EventFunction, bool>> >::iterator itr = allListeners.begin();
    for (; itr != allListeners.end(); )
    {
        std::vector<std::tuple<EventFunction, bool>> currentVec = std::get<1>(*itr);
        for (size_t i = 0; i < currentVec.size();)
        {
            // If the Event should automatically clear
            if (std::get<CLEAR>(currentVec[i]))
            {
                currentVec.erase(currentVec.begin() + i);
            }
            else
            {
                i++;
            }
        }

        if (currentVec.size() == 0)
        {
            itr = allListeners.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}

void EventSender::SendEventImmediately(const Event& event)
{
    //if (event.IgnorePause == false && SceneManagement::IsPaused())
    //{
    //    // this may be needed but seems to work fine without it
    //    //SceneManagement::AddPauseEventCallback(event);
    //    //return;
    //}

    std::string name = event.GetName();
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    // If there are no listeners for that event type just return
    if (allListeners.find(name) == allListeners.end())
    {
        // This isn't an error
        //std::string notes = "No listeners for the event type: " + name;
        //Errors::sendError(ERRPARAM, Errors::ErrorType::UNHANDLED, notes);
        return;

    }


    std::vector<std::tuple<EventFunction, bool>>& listeners = std::vector<std::tuple<EventFunction, bool>>();



    for (size_t i = 0; i < listeners.size(); i++)
    {
        EventFunction&& eventFunction = NULL;

        if (eventFunction != NULL)
        {
            //TRACE_SEND("Event was sent named " + name);
            eventFunction(event);
        }
    }
}