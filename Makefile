.PHONY: clean All

All:
	@echo "----------Building project:[ Test -  ]----------"
	@cd "Test" && "$(MAKE)" -f  "Test.mk"
clean:
	@echo "----------Cleaning project:[ Test -  ]----------"
	@cd "Test" && "$(MAKE)" -f  "Test.mk" clean
