double spring::findHeight(coordinate z)
{
    for(int a=wetTileHeights.size()-1; a>=0; a--)
    {
       if(wetTiles[a]==z)
       {
           return wetTileHeights[a];
       }
    }
    return 0;
}
