package com.fishjam.storehelper;

import java.util.ArrayList;

import android.R.integer;
import android.graphics.Point;

public final class FloorMapManager {

	public static FloorMapManager getInstance(){
		if (sInstanceOfFloorMapManager == null) {
			sInstanceOfFloorMapManager = new FloorMapManager();
		}
		return sInstanceOfFloorMapManager;
	}
	private static FloorMapManager	sInstanceOfFloorMapManager;
	private FloorMapManager(){
		mMapDatas = new ArrayList<FloorMapManager.MapData>();
		mMapDatas.add( new MapData(MapFloor1, ElevatorFloor1));
		mMapDatas.add( new MapData(MapFloor2, ElevatorFloor2));
	}
	
	
	public MapData getMapByFloor(int nFloor)
	{
		if (nFloor >= 0 && nFloor < mMapDatas.size()) {
			return mMapDatas.get(nFloor);
		}
		return null;
	}
	ArrayList<MapData> mMapDatas;
	
	
	public class MapData
	{
		MapData(int[][] titleData, Point[] elevatorData){
			mTileData = titleData;
			mElevatorData = elevatorData;
		}
		int [][] mTileData;
		Point [] mElevatorData;
	}
	
	private final static int[][] MapFloor1 = {
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,9,9,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,9,9,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,0,0,0,0,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,2,2,2,2,2,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }			
	};
	private final static Point[] ElevatorFloor1 = {
		new Point(9,30),
		new Point(10,30),
		new Point(9,31),
		new Point(10,31),
	};
	
	private final static int[][] MapFloor2 = {
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,3,8,8,8,8,8,8,8,7,7,7,7,7,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,9,9,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,9,9,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,9,9,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,7,7,7,7,7,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,0,8,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,0,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,0,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,0,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,0,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,0,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	
	private final static Point[] ElevatorFloor2 = {
		new Point(15,30),
	};
	public int getMapCount() {
		 
		return mMapDatas.size();
	}
}