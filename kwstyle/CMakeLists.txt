add_test(test_coding_rules KWStyle -v 
    -xml ${CMAKE_CURRENT_SOURCE_DIR}/Tetris.kws.xml 
    -D ${CMAKE_CURRENT_SOURCE_DIR}/FilesToCheck.txt
    )
