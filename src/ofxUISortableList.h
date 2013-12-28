/**********************************************************************************

 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 **********************************************************************************/

#ifndef OFXUI_DRAG_DROP_LIST
#define OFXUI_DRAG_DROP_LIST

#include "ofxUIToggle.h"

// TODO easing

class ofxUISortableList : public ofxUIButton
{
public:
    ofxUISortableList(string _name, vector<string> items, float w = 0, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM) : ofxUIButton(_name, false, w, h, x, y, _size)
    {
        init(_name, items, w, x, y, _size);
    }

    void init(string _name, vector<string> items, float w = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        itemHeight = 30;
        padding = 2;
        int height = items.size() * itemHeight + (padding*items.size() + padding);
        rect = new ofxUIRectangle(x,y,w,height);
        setParent(this);
        name = string(_name);
        kind = OFX_UI_WIDGET_SORTABLELIST;
        autoSize = false;

        label = new ofxUILabel(0, height+padding, (name+" LABEL"), name, _size);
        label->setParent(label); 
        label->setRectParent(rect); 
        label->setEmbedded(true);
        drawLabel = true;
        bLabelRight = false;
        label->setVisible(drawLabel);      

        activeWidget = 0;
        activeWidgetIndex = -1;
        initDragableElements(items, _size);
    }

    void setParent(ofxUIWidget *_parent)
    {
        parent = _parent;
        for(int i = 0; i < listItems.size(); i++)
        {
            ofxUIDraggableLabelButton *t = listItems[i];
            t->setParent(this);
            t->getRect()->setParent(this->getRect());
        }
    }

    vector<ofxUIDraggableLabelButton*> getListItems()
    {
        return listItems;
    }

    void reshuffle(std::vector<string> ordering)// reshuffle based on saved ordering
    {
        for (int i = 0; i < ordering.size(); i++)
        {
            ofxUIDraggableLabelButton* listItem =  listItems[i];
            if(listItem->getSortID()!=ordering.at(i))
            {
                for(int j = 0; j< listItems.size(); j++)
                {
                    ofxUIDraggableLabelButton* _listItem =  listItems[j];
                    if(_listItem->getSortID()==ordering.at(i))
                    {
                        // swap i, j
                        swapListItems(i, j);
                    }
                }
            }
        }
        refreshPositions();
    }

    void swapListItems(int swapA, int swapB)
    {
        std::swap(listItems[swapA], listItems[swapB]);
    }

    void mouseDragged(int x, int y, int button)
    {
        if(activeWidget)
        {
            ofxUIDraggableLabelButton* above;
            ofxUIDraggableLabelButton* below;
            int activeYPos = activeWidget->getY();
            bool isDirectionDown = lastActiveY < activeYPos;
            bool isDirectionUp = lastActiveY > activeYPos;
            lastActiveY = activeWidget->getY();

            if(isDirectionUp || isDirectionDown)// if there is change...
            {
                if(activeWidgetIndex>0 && (activeWidgetIndex < (listItems.size() - 1)))
                {
                    above = listItems.at(activeWidgetIndex - 1);
                    below = listItems.at(activeWidgetIndex + 1);
                    //call based on direction of travel
                    if(isDirectionUp && isInSwapZone(above))
                    {
                        goingUp();
                    }
                    if(isDirectionDown && isInSwapZone(below))
                    {
                        goingDown();
                    }
                }
                else if(activeWidgetIndex==0 || activeWidgetIndex==(listItems.size()-1))
                {
                    below = listItems.at(1);
                    above = listItems.at(listItems.size() - 1);
                    if(isDirectionDown && isInSwapZone(below))
                    {
                        goingDown();
                    }
                    if(isDirectionUp &&  isInSwapZone(above))
                    {
                        goingUp();
                    }
                }
            }
        }
    }

    void mousePressed(int x, int y, int button)
    {
        activeWidget = getActiveWidget(x, y);
        if(activeWidget)
        {
            // save the position from where it was dragged (in case we need to put it back there)
            int activeWidgetRectY = activeWidget->getRect()->getY();
            int rectY = getRect()->getY();
            saveY = activeWidgetRectY - rectY;
            lastActiveY = saveY;
        }
    }

    void mouseReleased(int x, int y, int button)
    {
        activeWidgetIndex = -1;
        refreshPositions();
        activeWidget = 0;
    }

protected:

    void initDragableElements(vector<string> &items, int _size)// build draggable widgets for the sortable items
    {
        float ty = padding;
        int width = rect->getWidth() - padding*2;
        for(int i = 0; i < items.size(); i++)
        {
            stringstream index;
            index << i;
            string tname = items[i];
            ofxUIDraggableLabelButton* listItem;
            listItem = new ofxUIDraggableLabelButton(tname, "", width, itemHeight, (int)(padding/2), ty, _size);
            listItem->setVisible(true);
            listItem->setLabelVisible(true);
            listItem->setSortID(tname + index.str());
            listItems.push_back(listItem);
            ty+=(itemHeight+padding);
        }
    }

    bool isInSwapZone(ofxUIDraggableLabelButton* swapCandidate)// the "swapZone" is the area that extends from adjacent elements, in which the active widget can be bumped up or down the list
    {
        int swapZoneHeight = activeWidget->getRect()->getHeight();

        int activeYPos = activeWidget->getY();
        int activeYBottom = activeWidget->getY() + swapZoneHeight;

        int candidateYPos = swapCandidate->getMidY();
        int candidateSwapZoneTop = candidateYPos - swapZoneHeight;
        int candidateSwapZoneBottom = candidateYPos + swapZoneHeight;

        if(activeYPos<candidateYPos && activeYPos>candidateSwapZoneTop)// if the top y position is in the swap zone
        {
            return true;
        }
        else if(activeYBottom>candidateYPos && activeYBottom<candidateSwapZoneBottom)// if the bottom y position is in the swap zone
        {
            return true;
        }
        return false;
    } 

    void goingUp()// what to do if the active widget is getting bumped up the list order
    {
        int swapIndex = activeWidgetIndex - 1;
        swapListItems(activeWidgetIndex, swapIndex);
        activeWidgetIndex--;
        refreshPositions();
    }

    void goingDown()// what to do if the active widget is getting bumped down the list order
    {
        int swapIndex = activeWidgetIndex + 1;
        swapListItems(activeWidgetIndex, swapIndex);
        activeWidgetIndex++;
        refreshPositions();
    }   

    void refreshPositions()// if the ordering changes - reflect it visually
    {
        float ty = padding;
        int width = rect->getWidth() - padding + 2;
        for (int i = 0; i < listItems.size(); i++)
        {
            if(activeWidgetIndex != i)
            {
                listItems.at(i)->setPos(padding, ty);
            }
            ty+=(itemHeight+padding);
        }
    }

    ofxUIDraggableLabelButton* getActiveWidget(int x, int y)
    {
        for (int i = 0; i < listItems.size(); i++)
        {
            if(listItems.at(i)->isHit(x, y))
            {
                activeWidgetIndex = i;
                return listItems.at(i);
            }
        }
        activeWidgetIndex = -1;
        return 0;
    }

    vector<ofxUIDraggableLabelButton*> listItems;
    bool autoSize;
    int itemHeight;
    int activeWidgetIndex;
    int saveY;
    int lastActiveY;
    ofxUIDraggableLabelButton* activeWidget;
};

#endif
