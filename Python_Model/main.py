from transformers import AutoTokenizer, AutoModelForCausalLM
import sys
import io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

model_name = "distilgpt2"
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModelForCausalLM.from_pretrained(model_name, device_map="auto")

def generate(prompt, profile):
    system_prompt = f"You're a {profile['tone']} assistant. You be {profile['style']}."
    full_prompt = system_prompt + "\nUser: " + prompt + "\nAI:"
    inputs = tokenizer(full_prompt, return_tensors="pt").to(model.device)
    outputs = model.generate(
        **inputs,
        max_new_tokens=200,
        do_sample=True,
        top_p=0.9,
        temperature=0.8,
        repetition_penalty=1.2,
    )
    generated_tokens = outputs[0][inputs['input_ids'].size(1):]
    return tokenizer.decode(generated_tokens, skip_special_tokens=True)


#Add lightweight customization hooks

#What's the difference between the real world and the virtual world?
#The presence of the cops.

print(generate("What's the difference between the real world and the virtual world?", {"tone": "realistic", "style": "humorous"}))

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python main.py <prompt> <tone> <style>")
        sys.exit(1)

    prompt = sys.argv[1]
    tone = sys.argv[2]
    style = sys.argv[3]

    profile = {"tone": tone, "style": style}
    response = generate(prompt, profile)
    print(response)
    
    
   # while True:
    #    prompt = input("You: ")
    #    if prompt.lower() in ("exit", "quit"):
    #        break
    #    response = generate(prompt, {"tone": "realistic", "style": "technical"})
    #    print("AI:", response)



    
    
    
    
    