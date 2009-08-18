/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#include "../../../../juce_core/basics/juce_StandardHeader.h"

BEGIN_JUCE_NAMESPACE

#include "juce_ChoicePropertyComponent.h"


//==============================================================================
ChoicePropertyComponent::ChoicePropertyComponent (const String& name)
    : PropertyComponent (name),
      comboBox (0)
{
}

ChoicePropertyComponent::~ChoicePropertyComponent()
{
    deleteAllChildren();
}

//==============================================================================
const StringArray& ChoicePropertyComponent::getChoices() const throw()
{
    return choices;
}

//==============================================================================
void ChoicePropertyComponent::refresh()
{
    if (comboBox == 0)
    {
        addAndMakeVisible (comboBox = new ComboBox (String::empty));

        for (int i = 0; i < choices.size(); ++i)
        {
            if (choices[i].isNotEmpty())
                comboBox->addItem (choices[i], i + 1);
            else
                comboBox->addSeparator();
        }

        comboBox->setEditableText (false);
        comboBox->addListener (this);
    }

    comboBox->setSelectedId (getIndex() + 1, true);
}

void ChoicePropertyComponent::comboBoxChanged (ComboBox*)
{
    const int newIndex = comboBox->getSelectedId() - 1;

    if (newIndex != getIndex())
        setIndex (newIndex);
}


END_JUCE_NAMESPACE
