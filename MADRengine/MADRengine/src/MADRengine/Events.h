#pragma once
#include "MADRpch.h"
#include <functional>
#include <map>
#include <variant>
#include "AK/SoundEngine/Common/AkSoundEngine.h"
#include "glm.hpp"
#include <array>
#include <any>


using string = std::string;

#define EventFunction(CLASS, FUNCTION) [CLASS](const Event& event) -> void {CLASS->FUNCTION(event); }
#define UnboundEventFunction(FUNCTION) [](const Event& event) -> void {FUNCTION(event); }
class Event
{
public:
    /*!*******************************************************************
        Creates an empty event. This will hold no data and should only be
        used as a bool.

    \param name
        The name of the event. This is NOT case-sensitive.
    \param priority
        A higher number will have it's listener's event functions
        executed first.

    \return
        The Event object.
    *********************************************************************/
    Event(std::string name, int priority);

    /*!*******************************************************************
        Creates an event with the provided data type.

    \param name
        The name of the event. This is NOT case-sensitive.
    \param priority
        A higher number will have it's listener's event functions
        executed first.
    \param data
        This is the data the event holds using std::variant.

    \return
        The Event object.
    *********************************************************************/
    Event(string name, int priority, std::any data, bool ignorePause = false);

    ~Event() {};

    string GetName() const;

    int priority = -1;

    std::any data = NULL;
    bool IgnorePause = false;

    void Send();

private:
    string name;
};


class EventListener
{
public:
    /*!*******************************************************************
        The generic function callback for EventListeners. This should always
        use std::holds_alternative<>() to ensure that the event is holding
        the data  type that you're expecting.
    *********************************************************************/
    virtual void EventResponse(const Event& event);
};


class EventSender
{
public:

    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    /*!*******************************************************************
        Get the singleton instance of the Event Sender. This ensures
        that there is only ever one EventSender because we want all the
        events and listener pointers stored in the same place.
    \return
        The EventSender object
    *********************************************************************/
    static EventSender& GetInstance()
    {
        static EventSender instance;
        return instance;
    }

    EventSender(EventSender const&) = delete;
    void operator=(EventSender const&) = delete;

    /*!*******************************************************************
        Event functions are a shorthand for an std::function that holds
        takes in a reference to an Event. This is what the callbacks
        should be prototyped as to make the system work with any data.
    *********************************************************************/
    using EventFunction = std::function<void(const Event&) >;

    /*!*******************************************************************
        Add a listener to the event system.
    *********************************************************************/
    void AddListener(const string& name, EventFunction eventFunc, bool clearAutomatic = true);

    /*!*******************************************************************
        Remve a listener from the event system.
    *********************************************************************/
    void RemoveListener(const string& name);

    void AutomaticRemoveListeners();

    void SendEventImmediately(const Event& event);
    void SendEventQueued(const Event& event);

private:

    EventSender() {}

    // The tuple holds an Eventfunction with a bool on whether or not it should be cleared automatically on scene change
    // Yes you're correct that I should never have three containers inside each other 
    std::map<string, std::vector<std::tuple<EventFunction, bool>> > allListeners;
};