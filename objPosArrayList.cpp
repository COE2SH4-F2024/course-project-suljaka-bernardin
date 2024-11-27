#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

// If it eats something you don't remove the one at the back

objPosArrayList::objPosArrayList()
{

    // This is defining the size of the array, as is done in the notes form Lecture 12

    aList = new objPos[ARRAY_MAX_CAP]; // NOTE: WATCH THIS IMPLEMENTATION --> This may not be what needs to be done here.
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;

    // Here we do not need to initialize the contents, because listSize will track how populated we are anyways
    
}

objPosArrayList::~objPosArrayList()
{

    // Standard deletion as seen in lecture


    delete[] aList;

}

// Time to respect the Rule of 6 / Minimum 4!

objPosArrayList::objPosArrayList(const objPosArrayList &a) {

    // Copying the ArrayCapacity and ListSize over

    arrayCapacity = a.arrayCapacity;
    listSize = a.listSize;

    // Creating the new ObjPosArrayList object

    aList = new objPos[ARRAY_MAX_CAP];

    // Deep copying the contents of aList, up to the size of listSize.

}

// Implementing the copy assignment constructor!

objPosArrayList& objPosArrayList::operator=(const objPosArrayList &a) {

    // We use the same this check as previously written in Player.cpp
    // Then just deep copy normally

    if (this != &a) {
        arrayCapacity = a.arrayCapacity;
        listSize = a.listSize;

        // Do our deep copy

        for (int i = 0; i < listSize; i++) {
            aList[i] = a.aList[i];
    }


    }

    return *this;


}

int objPosArrayList::getSize() const
{
    return listSize;

}

void objPosArrayList::insertHead(objPos thisPos)
{

    // In this function, we need to move everything backwards, then input the head
    // We do this by shifting everyting backwards.

    // First, a sanity check to ensure we are not above the arrayCap

    if (listSize > arrayCapacity) {
        // CRY!!!
        return;
    } else {

        // Doign the shifting of the list, starting from the index which is the farthest back, and going until the index of 0
        // This is because we do not want to hit the 0th index, since we index based on i-1!

        for (int i = listSize; i > 0; i--) {
            aList[i] = aList[i-1];
        }

        // Now, we assign the aList[0] value to the incomnig position object!

        aList[0] = thisPos;

        // We then increment sizeList to state that the list size has been increased by 1!

        listSize++;
    }


    
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // To insert the tail, it is far easier.  We just need to insert something at the very end of the list

    // We will return it the arrayCap = listSize, since we do not want to go over the arrayCapacity.

    // We also need a check to make sure the listSize is not equal to 0 already.

    if (listSize == arrayCapacity) {
        return;
    } else {
        // This is out main logic, which is just setting the value of listSize, and then incrementing it after the fact
        // ListSize acts like the size value of the array (where whatever indices you are at is listSize-1, hence post increment)

        aList[listSize] = thisPos;

        // Now, increment the listSize;

        listSize++;
    }
    
}

void objPosArrayList::removeHead()
{

    // For this function, we need to simply shift all of the elements forward, and then decreaese the list size by 1.
    // It's like lazy deletion.

    // Sanity check to ensure we are not already negataive first

    if (listSize <= 0) {
        return;
    } else {

        // We use listSize-1 here because we are dropping one element, and we are shifting the elements in i+1 forwards


        for (int i = 0; i < listSize - 1; i++) {
            aList[i] = aList[i+1];

        }

        // Finally, decrease the value of listSize;

        listSize--;
    }
    
}

void objPosArrayList::removeTail()
{
    // This is as easy as just decreasing the value of listSize!  Lazy deletion!

    if (listSize <= 0) {
        return;
    } else {
        listSize--;  
    }    
}

objPos objPosArrayList::getHeadElement() const
{

    // This one is fairly straightforward, we are simply returning element 0
    return aList[0];
    
}

objPos objPosArrayList::getTailElement() const
{

    // This one is slightly more challenging.  We have to return listSize-1 because of index offset

    return aList[listSize - 1];
    
}

objPos objPosArrayList::getElement(int index) const
{
    // For this one, we need to return the element at the index specified by the user

    // We will check it so that, if the index is less than 0, it will be reflected as 0
    // If the index is greater than or equal to the listSize, it will be changed to ListSize - 1;

    if (index < 0) {
        index = 0;
    } else if (listSize == 0) {
        index = listSize;
    } else if (index >= listSize) {
        index = listSize - 1;
    }

    // Now, we can return the index

    return aList[index];


    
}