# projectNaming sets the variable to the current directory name
# usage: 
# projectNaming(projectId)
# project({projectId})

function(PROJECTNAMING REQUIRED_ARGS) 
    get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(${REQUIRED_ARGS} ${ProjectId} PARENT_SCOPE)
endfunction()

