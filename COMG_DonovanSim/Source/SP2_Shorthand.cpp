#include "SP2.h"

void SP2::LoadShaderCodes()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Mapping variables to tell gpu what is what
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	for (size_t S = 0; S < numLights; S++)
	{
		std::string baseString = "lights[" + std::to_string(S);

		static vector<std::string> endings =
		{
			"].position_cameraspace",
			"].color",
			"].power",
			"].kC",
			"].kL",
			"].kQ",
			"].type",
			"].spotDirection",
			"].cosCutoff",
			"].cosInner",
			"].exponent"
		};

		vector<std::string>::iterator i = endings.begin();

		lightUniforms[S][UL_POSITION] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COLOR] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_POWER] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KC] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KL] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KQ] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_TYPE] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_SPOTDIRECTION] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COSCUTOFF] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COSINNER] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_EXPONENT] = glGetUniformLocation(m_programID, (baseString + *i).c_str());
	}

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);
}

void SP2::LoadLights()
{
	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(-60, 12, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.0f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.0f;
	light[0].spotDirection.Set(0.2f, 1.0f, 0.2f);

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 10, 0);
	light[1].color.Set(0, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.0f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.0f;
	light[1].spotDirection.Set(-0.2f, 1.0f, -0.2f);

	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(3, 10, 0);
	light[2].color.Set(1, 0, 0);
	light[2].power = 1;
	light[2].kC = 1.0f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.0f;
	light[2].spotDirection.Set(-0.2f, 1.0f, 0);

	glUniform1i(m_parameters[U_NUMLIGHTS], numLights);

	for (size_t S = 0; S < numLights; S++)
	{
		glUniform1i(lightUniforms[S][UL_TYPE], light[S].type);
		glUniform3fv(lightUniforms[S][UL_COLOR], 1, &light[S].color.r);
		glUniform1f(lightUniforms[S][UL_POWER], light[S].power);
		glUniform1f(lightUniforms[S][UL_KC], light[S].kC);
		glUniform1f(lightUniforms[S][UL_KL], light[S].kL);
		glUniform1f(lightUniforms[S][UL_KQ], light[S].kQ);
		glUniform1f(lightUniforms[S][UL_COSCUTOFF], light[S].cosCutoff);
		glUniform1f(lightUniforms[S][UL_COSINNER], light[S].cosInner);
		glUniform1f(lightUniforms[S][UL_EXPONENT], light[S].exponent);
	}

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], numLights);
}

void SP2::LoadMeshes()
{
	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//5.tga");

	//AXES
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//LIGHTBALL
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1));

	//SKYBOX
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//spaceground.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//purplenebula_ft_hd.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//purplenebula_bk_hd.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//purplenebula_up_hd.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//purplenebula_dn_hd.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//purplenebula_lf_hd.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//purplenebula_rt_hd.tga");

	//WALLS
	meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//TestWall2.obj");
	meshList[GEO_WALL]->textureID = LoadTGA("Image//TestWall.tga");

	meshList[GEO_WALL2] = MeshBuilder::GenerateOBJ("wall2", "OBJ//TestWall.obj");
	meshList[GEO_WALL2]->textureID = LoadTGA("Image//TestWall.tga");

	meshList[GEO_GATETOP] = MeshBuilder::GenerateOBJ("wall", "OBJ//TESTDOOR.obj");
	meshList[GEO_GATETOP]->textureID = LoadTGA("Image//gateTopUV.tga");

	meshList[GEO_GATE] = MeshBuilder::GenerateOBJ("wall", "OBJ//gate.obj");
	meshList[GEO_GATE]->textureID = LoadTGA("Image//gateUV.tga");

	//GROUND MESH
	meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("ground", Color(1, 1, 1));
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleFloor.tga");

	meshList[GEO_GROUND]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
	meshList[GEO_GROUND]->material.kDiffuse.Set(0.6, 0.6, 0.6);
	meshList[GEO_GROUND]->material.kSpecular.Set(0.4, 0.4, 0.4);
	meshList[GEO_GROUND]->material.kShininess = 1;

	//TRADE POST
	meshList[GEO_TRADEPOST] = MeshBuilder::GenerateOBJ("Tradepost", "OBJ//TradingPost.obj");
	meshList[GEO_TRADEPOST]->textureID = LoadTGA("Image//TradingPostTexture2.tga");

	//CRYSTAL
	meshList[GEO_CRYSTAL] = MeshBuilder::GenerateOBJ("Crystal", "OBJ//crystal2.obj");
	meshList[GEO_CRYSTAL]->textureID = LoadTGA("Image//crystal_Tile.tga");
	InteractableOBJs crystal = InteractableOBJs("crystal", meshList[GEO_CRYSTAL]->maxPos, meshList[GEO_CRYSTAL]->minPos, Position(-100, 0, -100), 2, 0, Vector3(0, 0, 0));
	crystal.setRequirements(30, 5);
	InteractablesList.push_back(crystal);
	//init collision, then render room

	////CAFE
	//initRoomTemplate(Position(150, 2, 0));          //Collision

	//COUNTER
	meshList[GEO_COUNTER] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Counter.obj");
	meshList[GEO_COUNTER]->textureID = LoadTGA("Image//Counter.tga");
	InteractableOBJs counter = InteractableOBJs("counter", meshList[GEO_COUNTER]->maxPos, meshList[GEO_COUNTER]->minPos, Position(280, 2, 0), 3, 0, Vector3(0, 0, 0));
	counter.setRequirements(40, 15);
	InteractablesList.push_back(counter);

	//FRIDGE
	meshList[GEO_FRIDGE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Fridge.obj");
	meshList[GEO_FRIDGE]->textureID = LoadTGA("Image//Fridge.tga");

	//CHEF
	meshList[GEO_CHEF] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Chef.obj");
	meshList[GEO_CHEF]->textureID = LoadTGA("Image//Chef.tga");


	//TABLE
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table.tga");

	//VENDING
	meshList[GEO_VENDING] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Vending.obj");
	meshList[GEO_VENDING]->textureID = LoadTGA("Image//Vending.tga");
	InteractableOBJs vending = InteractableOBJs("vending", meshList[GEO_VENDING]->maxPos, meshList[GEO_VENDING]->minPos, Position(220, 10, 70), 3, 0, Vector3(0, 0, 0));
	vending.setRequirements(52, 15);  //55, 15
	InteractablesList.push_back(vending);

	//CHAIR
	/*meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//Chair.tga");*/

	//Token
	meshList[GEO_TOKEN] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Token.obj");
	meshList[GEO_TOKEN]->textureID = LoadTGA("Image//Token.tga");
	InteractableOBJs token = InteractableOBJs("token", meshList[GEO_TOKEN]->maxPos, meshList[GEO_TOKEN]->minPos, Position(276, TokenTranslate, 61), 2, 0, Vector3(0, 0, 0));
	token.setRequirements(30, 5);
	InteractablesList.push_back(token);

	//COKE
	meshList[GEO_COKE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Coke.obj");
	meshList[GEO_COKE]->textureID = LoadTGA("Image//Coke.tga");

	//CAFE MENU TEXT BOX
	meshList[GEO_CAFETEXTBOX] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//TextBoxCafeMenu.obj");
	meshList[GEO_CAFETEXTBOX]->textureID = LoadTGA("Image//Token.tga");




	////RECREATIOMAL ROOM
	//initRoomTemplate(Position(20, 2, 0));            //Collision

	//SPEAKERS
	meshList[GEO_SPEAKERS] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//RecRoomSpeakers.obj");
	meshList[GEO_SPEAKERS]->textureID = LoadTGA("Image//RecRoomSpeakers.tga");

	//SOFA
	meshList[GEO_SOFA] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//sofa.obj");
	meshList[GEO_SOFA]->textureID = LoadTGA("Image//sofa.tga");




	//BUNK
	meshList[GEO_BUNK] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Bunk.obj");
	meshList[GEO_BUNK]->textureID = LoadTGA("Image//Bunk.tga");

	//NPC
	meshList[GEO_SPACEGUY] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Spaceman.obj");
	meshList[GEO_SPACEGUY]->textureID = LoadTGA("Image//Spaceman.tga");

	//SPACESUIT
	meshList[GEO_SPACESUIT] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Spacesuit.obj");
	meshList[GEO_SPACESUIT]->textureID = LoadTGA("Image//Spacesuit.tga");
	InteractableOBJs spacesuit = InteractableOBJs("spacesuit", meshList[GEO_SPACESUIT]->maxPos, meshList[GEO_SPACESUIT]->minPos, Position(220, SuitTranslate, 190), 2, 0, Vector3(0, 0, 0));
	spacesuit.setRequirements(25, 15);
	InteractablesList.push_back(spacesuit);

	//SPACE MASK
	meshList[GEO_SPACEMASK] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Spacemask.obj");
	meshList[GEO_SPACEMASK]->textureID = LoadTGA("Image//Spacemask.tga");

    initRoomTemplate(Position(250, 2, 160));

    initRoomTemplate(Position(250, 2, 30));  //CAFE ROOM

    initRoomTemplate(Position(250, 2, -100));
 
    initRoomTemplate(Position(120, 2, 160));

    initRoomTemplate(Position(120, 2, 30));

    initRoomTemplate(Position(120, 2, -100));

    initSpaceShip();
}

void SP2::initSpaceShip()
{
    // Space Ship
    meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");
    Ship someShip = Ship("ship", meshList[GEO_SHIP]->maxPos, meshList[GEO_SHIP]->minPos, shipStartingPos, 4, 0, Vector3(0, 0, 0));
    someShip.setRequirements(50, 500);

    shipTemplatePtr = &someShip;
}

void SP2::initRoomTemplate(Position pos, Vector3 size, int groundMeshSize)
{
	Building floor1 = Building("floor1", meshList[GEO_GROUND]->maxPos, meshList[GEO_GROUND]->minPos, Position(pos.x, pos.y, pos.z - 20), groundMeshSize, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(floor1);

	Building ceiling1 = Building("ceiling1", meshList[GEO_GROUND]->maxPos, meshList[GEO_GROUND]->minPos, Position(pos.x, pos.y + 30, pos.z - 20), groundMeshSize, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(ceiling1);


	Building rightWall1 = Building("rightWall1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x + 38, pos.y + heightOfWall, pos.z + (groundMeshSize / 2)), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(rightWall1);

	Building rightWall2 = Building("rightWall2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x - 38, pos.y + heightOfWall, pos.z + (groundMeshSize / 2)), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(rightWall2);

	InteractableOBJs rightGateTop = InteractableOBJs("rightGateTop", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x, pos.y + 15, pos.z + (groundMeshSize / 2)), 5, 0, Vector3(0, 0, 0));
    rightGateTop.setRequirements(52, 15);
    //InteractablesList.push_back(rightGateTop);


	Building leftWall1 = Building("leftWall1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x + 38, pos.y + heightOfWall, pos.z - (groundMeshSize / 2)), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(leftWall1);

	Building leftWall2 = Building("leftWall2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x - 38, pos.y + heightOfWall, pos.z - (groundMeshSize / 2)), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(leftWall2);

	InteractableOBJs leftGateTop = InteractableOBJs("leftGateTop", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x, pos.y + 15, pos.z - (groundMeshSize / 2)), 5, 0, Vector3(0, 0, 0));
    leftGateTop.setRequirements(52, 15);
    //InteractablesList.push_back(leftGateTop);


	Building frontWall1 = Building("frontWall1", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + heightOfWall, pos.z - 38), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(frontWall1);

	Building frontWall2 = Building("frontWall2", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + heightOfWall, pos.z + 38), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(frontWall2);

    InteractableOBJs frontGateTop = InteractableOBJs("frontGateTop", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + 15, pos.z), 5, 0, Vector3(0, 0, 0));
    frontGateTop.setRequirements(52, 15);
    //InteractablesList.push_back(frontGateTop);


	Building backWall1 = Building("backWall1", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + heightOfWall, pos.z - 38), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(backWall1);

	Building backWall2 = Building("backWall2", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + heightOfWall, pos.z + 38), 12, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(backWall2);

    InteractableOBJs backGateTop = InteractableOBJs("backGateTop", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + 15, pos.z), 5, 0, Vector3(0, 0, 0));
    backGateTop.setRequirements(52, 15);
    //InteractablesList.push_back(backGateTop);

}

void SP2::ReadKeyPresses()
{
	if (Application::IsKeyPressed('B'))
	{
		if (toggleLight == true)
		{
			toggleLight = false;
		}
		else
		{
			toggleLight = true;
		}
	}

	//COLLECT TOLKEN
	if (Application::IsKeyPressed('Q'))
	{
		TokenOnScreen = true;
		TokenTranslate = 10.5;
	}
}

//Main Render code.
void SP2::RenderCode()
{
    //RENDER LIGHTBALL
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(thirdPersonCamera.GetFocusPoint()->x, thirdPersonCamera.GetFocusPoint()->y, thirdPersonCamera.GetFocusPoint()->z);
	RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();

	if (ShipList.size() > 0)
	{
		modelStack.PushMatrix();
		modelStack.Translate(shipPos.x, shipPos.y, shipPos.z);
		modelStack.Scale(6, 6, 6);
		RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
		modelStack.PopMatrix();

		RenderSpaceShip();
	}


	//RENDER SKYBOX
	RenderSkybox();


	//RENDER CAFE
	RenderCafeRoom();

	//RENDER BUNK
	RenderBunkRoom();

	//GROUND MESH
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], true, toggleLight);
	modelStack.PopMatrix();

	////GROUND MESH
	//modelStack.PushMatrix();
	//modelStack.Translate(250, 0, 50);
	//RenderMesh(meshList[GEO_HAND], true, toggleLight);
	//modelStack.PopMatrix();

	////RenderHand
	//RenderHandOnScreen(meshList[GEO_HAND], 5, 1, 1);


	//TRADING STATION
	//modelStack.PushMatrix();
	//RenderRoomTemplate(Position(100, 2, 0));
	//modelStack.Translate(100, 2, 0);
	//RenderTradingStation();
	//modelStack.PopMatrix();

	////RENDER ROOM (WALLS)
	//RenderRoomTemplate(Position(20, 2, 0));     //RECREATIONAL ROOM


	//RENDER ROOM (WALLS)
	//RenderRoomTemplate(Position(150, 2, 0));   //CAFE

	////RENDER ROOM (WALLS)
	//RenderRoomTemplate(Position(280, 2, 0));   //SPACE ENGINE ROOM

	////RENDER ROOM (WALLS)
	//RenderRoomTemplate(Position(150, 2, 150));   //BUNK ROOM

	RenderRoomTemplate(Position(250, 2, 160));   

	RenderRoomTemplate(Position(250, 2, 30));  //CAFE ROOM

	RenderRoomTemplate(Position(250, 2, -100));



	RenderRoomTemplate(Position(120, 2, 160));

	RenderRoomTemplate(Position(120, 2, 30));

    RenderRoomTemplate(Position(120, 2, -100));

	//RenderRoomTemplate(Position(120, 2, -100));

	//INTERACTIONS

    // SpaceShip
    //modelStack.PushMatrix();
    //modelStack.Translate(thirdPersonCamera.GetFocusPoint()->x, thirdPersonCamera.GetFocusPoint()->y - 30, thirdPersonCamera.GetFocusPoint()->z + 80);
    //modelStack.Translate(thirdPersonCamera.target.x, thirdPersonCamera.target.y, thirdPersonCamera.target.z);
    //modelStack.Rotate(shipRotateAngle, 1, 1, 1);
    //modelStack.Scale(4, 4, 4);
    //RenderMesh(meshList[GEO_SHIP], true, toggleLight);
    //modelStack.PopMatrix();



	// Mine
	//modelStack.PushMatrix();
	//modelStack.Translate(-100, 2, 50);
	//modelStack.Scale(4, 4, 4);
	//RenderMesh(meshList[GEO_MINE], true, toggleLight);
	//modelStack.PopMatrix();

	if (!HoldCrystal)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-100, 2, -100);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_CRYSTAL], true, toggleLight);
		modelStack.PopMatrix();
	}

	// POSITION OF X Y Z
	std::ostringstream ss;
	ss.str("");
	ss << "Position: X(" << camera5.position.x << ") Y(" << camera5.position.y << ") Z(" << camera5.position.z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 1.2f, 3, 4);

	//VENDING TEXT
	if (NearVendingText)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Requires token", Color(1, 0, 0), 2, 6, TextTranslate);
	}

	if (TokenOnScreen == true)
	{
		RenderTokenOnScreen(meshList[GEO_TOKEN], 5, 8, 6);
	}

	//TEST TEXT
	if (testText == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "testTESTtest", Color(1, 0, 0), 2, 6, 14);
	}

	//PICK UP TOKEN
	if (PickUpTokenText == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "PRESS Q TO PICK UP TOKEN", Color(1, 0, 0), 2, 6, 18);
	}

	//PICK UP COKE
	if (RenderCoke == true)
	{
		RenderCokeOnScreen(meshList[GEO_COKE], 5, 8, 6);
	}

	//CONSUME COKE TEXT
	if (ConsumeCokeText == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "THANKS FOR BUYING A COKE!!", Color(1, 0, 0), 2, 6, 22);
		RenderTextOnScreen(meshList[GEO_TEXT], "HERE IS YOUR COKE.", Color(1, 0, 0), 2, 6, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "PRESS U TO DRINK COKE", Color(1, 0, 0), 2, 6, 18);
	}

	//Cafe menu
	if (DisplayCafeMenu == true)
	{
		RenderCafeTextboxOnScreen(meshList[GEO_CAFETEXTBOX], 5, 8, 6);
	}


	//Mining  
	if ((NearCrystal) && HoldCrystal == false )
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press O to pick up crystal", Color(1, 0, 0), 2, 6, TextTranslate);
	}

	if (HoldCrystal == true)   
	{
		RenderCrystalOnScreen(meshList[GEO_CRYSTAL], 5, 8, 6);
    }
	//WEAR SUIT TEXT
	if (wearSuitText == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "PRESS T TO PUT ON SPACE SUIT", Color(1, 0, 0), 2, 6, 18);
	}

	//WEAR SUIT \ MASK ON SCREEN
	if (wearSuit == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "PRESS T TO PUT ON SPACE SUIT", Color(1, 0, 0), 2, 8, 14);
		RenderCafeTextboxOnScreen(meshList[GEO_CAFETEXTBOX], 5, 8, 6);

	}
}

void SP2::RenderRoomTemplate(Position pos, Vector3 size, int groundMeshSize)
{
	groundMeshSize = 100;

	// Whole Room
	modelStack.PushMatrix();
	modelStack.Translate(pos.x, pos.y, pos.z);

	// Render Floor + Ceiling
	modelStack.PushMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(groundMeshSize, groundMeshSize, groundMeshSize);
	RenderMesh(meshList[GEO_GROUND], false, toggleLight); // Floor
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(groundMeshSize, groundMeshSize, groundMeshSize);
	RenderMesh(meshList[GEO_GROUND], false, toggleLight); // Ceiling
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	// Render Walls
	modelStack.PushMatrix();

	// ---------------------------- Right Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, (groundMeshSize / 2));

	modelStack.PushMatrix();
	modelStack.Translate(38, heightOfWall, 0);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-38, heightOfWall, 0);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
    modelStack.Translate(0, 15 + gateOffset, 0);
    modelStack.Scale(3, 9, 3);
	//RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Right Wall ---------------------------------- //


	// ---------------------------- Left Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -(groundMeshSize / 2));

	modelStack.PushMatrix();
	modelStack.Translate(38, heightOfWall, 0);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-38, heightOfWall, 0);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
    modelStack.Translate(0, 15 + gateOffset, 0);
    modelStack.Scale(3, 9, 3);
	//RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Left Wall ---------------------------------- //


	// ---------------------------- Front Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate((groundMeshSize / 2), 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, -38);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, 38);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
    modelStack.Translate(0, 15 + gateOffset, 0);
	modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(3, 9, 3);
	//RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Front Wall ---------------------------------- //


	// ---------------------------- Back Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate((-groundMeshSize / 2), 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, -38);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, 38);
    modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
    modelStack.Translate(0, 15 + gateOffset, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 9, 3);
	//RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Back Wall ---------------------------------- //

	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void SP2::RenderSkybox()
{
	// FRONT
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(camera5.position.x, camera5.position.y, -249.5 + camera5.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, thirdPersonCamera.position.y, -249.5 + thirdPersonCamera.position.z);
	//}

	modelStack.Translate(somePlayer.pos.x, somePlayer.pos.y, -500 + somePlayer.pos.z);

	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false, toggleLight);
	modelStack.PopMatrix();

	// BACK
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(camera5.position.x, camera5.position.y, 249.5 + camera5.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, thirdPersonCamera.position.y, 249.5 + thirdPersonCamera.position.z);
	//}

	modelStack.Translate(somePlayer.pos.x, somePlayer.pos.y, 500 + somePlayer.pos.z);

	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false, toggleLight);
	modelStack.PopMatrix();

	// LEFT
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(-249.5 + camera5.position.x, camera5.position.y, camera5.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(-249.5 + thirdPersonCamera.position.x, thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}

	modelStack.Translate(-500 + somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z);

	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false, toggleLight);
	modelStack.PopMatrix();

	// RIGHT
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(249.5 + camera5.position.x, camera5.position.y, camera5.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(249.5 + thirdPersonCamera.position.x, thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}

	modelStack.Translate(500 + somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z);

	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false, toggleLight);
	modelStack.PopMatrix();

	// BOTTOM
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(camera5.position.x, -249.5 + camera5.position.y, camera5.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, -249.5 + thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}
	//modelStack.Scale(500, 500, 500);

	modelStack.Translate(somePlayer.pos.x, -500 + somePlayer.pos.y, somePlayer.pos.z);
	modelStack.Scale(1000, 1000, 1000);

	RenderMesh(meshList[GEO_BOTTOM], false, toggleLight);
	modelStack.PopMatrix();

	// TOP
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(camera5.position.x, 249.5 + camera5.position.y, camera5.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, 249.5 + thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}

	modelStack.Translate(somePlayer.pos.x, 500 + somePlayer.pos.y, somePlayer.pos.z);

	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderBunkRoom()
{
	//BUNK 1 
	modelStack.PushMatrix();
	modelStack.Translate(288, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//BUNK 2 
	modelStack.PushMatrix();
	modelStack.Translate(271, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();


	//BUNK 3 
	modelStack.PushMatrix();
	modelStack.Translate(210, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//BUNK 4 
	modelStack.PushMatrix();
	modelStack.Translate(227, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();



	//BUNK 5 
	modelStack.PushMatrix();
	modelStack.Translate(288, 3, 191.5);
	modelStack.Scale(1.2, 1.2, 1.2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//BUNK 6 
	modelStack.PushMatrix();
	modelStack.Translate(271, 3, 191.5);
	modelStack.Scale(1.2, 1.2, 1.2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//SPACE MAN RANDOM NPC
	modelStack.PushMatrix();
	modelStack.Translate(271, 1.9, 143);
	modelStack.Scale(3.4, 4.4, 3.4);
	RenderMesh(meshList[GEO_SPACEGUY], true, toggleLight);
	modelStack.PopMatrix();

	//SPACESUIT
	modelStack.PushMatrix();
	modelStack.Translate(220, SuitTranslate, 190);
	modelStack.Scale(1.3, 1.3, 1.3);
	modelStack.Rotate(180 , 0, 1, 0);
	RenderMesh(meshList[GEO_SPACESUIT], true, toggleLight);
	modelStack.PopMatrix();


	glBlendFunc(1, 1);
	modelStack.PushMatrix();
	modelStack.Translate(220, 10, 190);
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_SPACEMASK], true, toggleLight);
	modelStack.PopMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SP2::RenderCafeRoom()
{
	//COUNTER
	modelStack.PushMatrix();
	modelStack.Translate(280, 2, 0);
	modelStack.Scale(2.3, 2, 2.3);
	RenderMesh(meshList[GEO_COUNTER], true, toggleLight);
	modelStack.PopMatrix();

	//FRIDGE
	modelStack.PushMatrix();
	modelStack.Translate(295, 2, -13);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_FRIDGE], true, toggleLight);
	modelStack.PopMatrix();

	//CHEF
	modelStack.PushMatrix();
	modelStack.Translate(280, 2, -2);
	modelStack.Scale(3.5, 3.8, 3.5);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_CHEF], true, toggleLight);
	modelStack.PopMatrix();

	//TABLE
	modelStack.PushMatrix();
	modelStack.Translate(280, 2, 65);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_TABLE], true, toggleLight);
	modelStack.PopMatrix();

	////CHAIR 1
	//modelStack.PushMatrix();
	//modelStack.Translate(270, 2, 65);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[GEO_CHAIR], true, toggleLight);
	//modelStack.PopMatrix();

	////CHAIR 2
	//modelStack.PushMatrix();
	//modelStack.Translate(290, 2, 65);
	//modelStack.Scale(2, 2, 2);
	//modelStack.Rotate(180, 0, 1, 0);
	//RenderMesh(meshList[GEO_CHAIR], true, toggleLight);
	//modelStack.PopMatrix();

	//TOKEN
	modelStack.PushMatrix();
	modelStack.Translate(276, TokenTranslate, 61);
	modelStack.Scale(1, 1.5, 1);
	RenderMesh(meshList[GEO_TOKEN], true, toggleLight);
	modelStack.PopMatrix();

	//VENDING
	modelStack.PushMatrix();
	modelStack.Translate(210, 2, 88);
	modelStack.Scale(2.5, 2.5, 2.5);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_VENDING], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderTokenOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderCokeOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderCafeTextboxOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderHandOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	//modelStack.Rotate(-20, 0, 1, 0);
	//modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderSpacemaskOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	//modelStack.Rotate(-20, 0, 1, 0);
	//modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderRecRoom()
{
	//SOFA
	modelStack.PushMatrix();
	modelStack.Translate(155, 2, 65);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	//SPEAKER
	modelStack.PushMatrix();
	modelStack.Translate(10, 17, 10);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPEAKERS], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderCrystalOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SP2::RenderTradingStation()
{
	//TRADING STATION
	modelStack.PushMatrix();
	modelStack.Translate(-5, 0, 5);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_TRADEPOST], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderSpaceShip()
{
    // Start of SpaceShip
    modelStack.PushMatrix();

	modelStack.Translate(shipPos.x, shipPos.y, shipPos.z);

    //if (thirdPersonCamera.yawingLeft == true || thirdPersonCamera.yawingRight == true) { modelStack.Rotate(shipHorizontalRotateAngle, 0, 1, 0); }
    //if (thirdPersonCamera.pitchingDown == true || thirdPersonCamera.pitchingUp == true) { modelStack.Rotate(shipVerticalRotateAngle, 0, 0, 1); }

    // Rotate Ship By its own Axis
    modelStack.Rotate(shipHorizontalRotateAngle, 0, 1, 0);
    modelStack.Rotate(shipVerticalRotateAngle, 1, 0, 1);

    // Scale Ship
    modelStack.Scale(4, 4, 4); 

    RenderMesh(meshList[GEO_HULL], true, toggleLight);
    RenderMesh(meshList[GEO_WINGS], true, toggleLight);
    RenderMesh(meshList[GEO_ENGINE], true, toggleLight);

    modelStack.PopMatrix();
    // End of SpaceShip
}

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);


	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

