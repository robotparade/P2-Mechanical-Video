    int myBumpSensor = 0;
    enable_servos();
    create_connect();
    printf("create connected");
    
    //starting positions for servos/////////////////////////////////////////////////////////////
    set_servo_position(0, 450);
    set_servo_position(1, 1300);
    set_servo_position(2, 2047);
    set_servo_position(3, 500);
    
//go forward until middle black line//////////////////////////////////////////////////////////////
    create_drive_direct(80, 80);
   msleep(8000);
    while(analog(0) < 3000)
    {
        if(analog(0) > 3000)
        {
            ao();
            printf("saw the line");
            break;
            
        }
    }
      
    //move backward//////////////////////////////////////////////////////////////////////////////////
    create_drive_direct(-50, -50);
    msleep(3500);
    ao();
    
    //turn right///////////////////////////////////////////////////////////////////////////////////
    
    create_drive_direct(50, -50);
    msleep(3430);
    ao();
    //line follow until lined up to gas line/////////////////////////////////////////////////////

    create_drive_direct(80, 80);
    msleep(10000);
    ao();
    
    //turn left until camera sees orange gas pipe (put existing code here)/////////////////////////
    
    
     //declare integer as object found
    int objectFound = 0;

    //declare color channel
    int myColorChannel = 1; //0 = green    1 = orange    2 = red   3 = blue///////////////////////

 

    //report that the program has started
    printf(" Camera Program has started. \n");
    msleep(2000);

    //turn camera on
    camera_open_black();

    //load configuration for camera
    if (camera_load_config("dining room"))
    {
        printf("camera_load_config(); succeeded!");
    }



    //spin the robot in a circle
  create_drive_direct(-50, 50);

    //loop until object is found
    while (objectFound == 0)
    {
        //update camera
        camera_update();

        //get information from the camera
        //test to see if objects are found
        if (get_object_count(myColorChannel) > 0)
        {
            printf("Object has been found");
            msleep(500);
            ao();
            objectFound = (objectFound + 1);
            //stop program because objects were found

        }
    }
    //report back how many objects and where they are on the screen
    printf("Number of objects found = %d \n", get_object_count(0));

    printf("object x column = %d \n",get_object_center_x(myColorChannel, 0));
    printf("object y row = %d \n", get_object_center_y(myColorChannel, 0));

    //print object area
    printf("object area = %d \n", get_object_area(myColorChannel, 0));


    //go forward until bumped///////////////////////////////////////////////////////////////////////
    create_drive_direct(50, 50);
    while(myBumpSensor == 0)
    {
    if(get_create_rbump() == 1)
    {
        ao();
        printf("bump sensor activated");
        break;
    }
    }
    //move backward until black line sensed////////////////////////////////////////////////////////////////////////////
    create_drive_direct(-50, -50);
        while(analog(0) < 3500)
    {
        if((analog(0) > 200) && (analog(0) < 350))
        {
            ao();
            printf("saw the line");
            break;
            
        }
    }
    
    
    //set servo position to safe
    set_servo_position(1, 1100);
    
    //turn right
    create_drive_direct(50, -50);
    msleep(3600);
    ao();
    
    //drive until bumped
    create_drive_direct(50 ,50);
	while(get_create_lbump() == 0);
    {
        create_drive_direct(50, 50);

    }
    
    //move backward
    create_drive_direct(-50, -50);
    msleep(1000);
    ao();






























